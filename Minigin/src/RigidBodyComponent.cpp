#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "Physics.h"
#include "PhysicsConvert.h"
#include "Renderer.h"

#include <box2d/box2d.h>

#include "ColliderComponent.h"

namespace dae
{
	RigidBodyComponent::RigidBodyComponent(const glm::vec2& size, RigidBodyType type)
		: m_Size(size), m_Type(type)
	{
	}

	void RigidBodyComponent::ApplyForce(const glm::vec2& force)
	{
		m_pBody->ApplyForceToCenter({ force.x, force.y }, true);
	}

	void RigidBodyComponent::ApplyImpulse(const glm::vec2& impulse)
	{
		m_pBody->ApplyLinearImpulseToCenter({ impulse.x, impulse.y }, true);
	}

	void RigidBodyComponent::OnPrepare()
	{
		b2BodyType bodyType = b2_staticBody;
		switch (m_Type)
		{
		case RigidBodyType::Static:
			bodyType = b2_staticBody;
			break;
		case RigidBodyType::Dynamic:
			bodyType = b2_dynamicBody;
			break;
		case RigidBodyType::Kinematic:
			bodyType = b2_kinematicBody;
			break;
		}

		const glm::vec2 objPos = GetGameObject()->GetTransform()->GetPosition();
		const float ppm = Physics::GetInstance().GetPPMRatio();

		b2BodyDef bodyDef;
		bodyDef.type = bodyType;
		bodyDef.position.Set((objPos.x + m_Size.x / 2) / ppm, (objPos.y + m_Size.y / 2) / ppm);
		bodyDef.fixedRotation = true; // Hard-coded for now, might become a parameter in the future.
		m_pBody = Physics::GetInstance().GetWorld()->CreateBody(&bodyDef); // Todo: make physics world part of the scene.

		const std::vector<ColliderComponent*> colliders = m_pGameObject->GetComponents<ColliderComponent>();
		for (const ColliderComponent* pCollider : colliders)
		{
			const glm::vec2 size = pCollider->GetSize();
			const glm::vec2 offset = pCollider->GetOffset();

			b2Vec2 center = PhysicsConvert::ToBox2DVec(offset);
			center.x /= ppm;
			center.y /= ppm;
			
			b2PolygonShape boxShape;
			boxShape.SetAsBox((size.x / 2) / ppm, (size.y / 2) / ppm, center, 0.0f);

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &boxShape;
			fixtureDef.density = pCollider->GetIsTrigger() ? 0.0f : 1.0f;
			fixtureDef.friction = 0.5f;
			fixtureDef.isSensor = pCollider->GetIsTrigger();

			m_pBody->CreateFixture(&fixtureDef);
		}
	}

	void RigidBodyComponent::OnPhysicsUpdate()
	{
		const b2Vec2 pos = m_pBody->GetPosition();
		const float angle = m_pBody->GetAngle();
		const float ppm = Physics::GetInstance().GetPPMRatio();

		m_pGameObject->GetTransform()->SetPosition({ (pos.x * ppm) - (m_Size.x / 2), (pos.y * ppm) - (m_Size.y / 2), 0.0f });
		m_pGameObject->GetTransform()->SetRotation(angle);
	}

	void RigidBodyComponent::OnImGui()
	{
		Color c = Color(1.0f, 1.0f, 1.0f, 1.0f);
		switch (m_Type)
		{
		case RigidBodyType::Dynamic:
			c = Color(1.0f, 0.0f, 0.0f);
			break;
		case RigidBodyType::Static:
			c = Color(0.0f, 1.0f, 0.0f);
			break;
		case RigidBodyType::Kinematic:
			c = Color(0.0f, 0.0f, 1.0f);
			break;
		}

		for (b2Fixture* pFixture = m_pBody->GetFixtureList(); pFixture; pFixture = pFixture->GetNext())
		{
			switch (pFixture->GetType())
			{
			case b2Shape::e_polygon:
				{
					b2PolygonShape* polygon = reinterpret_cast<b2PolygonShape*>(pFixture->GetShape());

					const int32 count = polygon->m_count;
					for (int32 i = 1; i < count; i++)
					{
						const glm::vec2 prev = PhysicsConvert::ToGlmVec(m_pBody->GetWorldPoint(polygon->m_vertices[i - 1]))
							* Physics::GetInstance().GetPPMRatio();
						const glm::vec2 current = PhysicsConvert::ToGlmVec(m_pBody->GetWorldPoint(polygon->m_vertices[i]))
							* Physics::GetInstance().GetPPMRatio();

						Renderer::GetInstance().DebugRenderLine(prev, current, c);
					}

					const glm::vec2 prev = PhysicsConvert::ToGlmVec(m_pBody->GetWorldPoint(polygon->m_vertices[count - 1]))
							* Physics::GetInstance().GetPPMRatio();
					const glm::vec2 current = PhysicsConvert::ToGlmVec(m_pBody->GetWorldPoint(polygon->m_vertices[0]))
							* Physics::GetInstance().GetPPMRatio();

					Renderer::GetInstance().DebugRenderLine(prev, current, c);

					break;
				}
			default:;
			}
		}
	}
}

﻿#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "Physics.h"
#include "PhysicsConvert.h"
#include "Renderer.h"

#include <box2d/box2d.h>

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

	void RigidBodyComponent::UpdateBodyTransform(const glm::vec2& position, float rotation)
	{
		UNREFERENCED_PARAMETER(position);
		UNREFERENCED_PARAMETER(rotation);

		// m_pBody->SetTransform({ position.x, position.y }, rotation);
		// m_pBody->SetLinearVelocity({ 0.0f, 0.0f });
		// m_pBody->SetAngularVelocity(0.0f);
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
		m_pBody = Physics::GetInstance().GetWorld()->CreateBody(&bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox((m_Size.x / 2) / ppm, (m_Size.y / 2) / ppm);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.5f; // Hard-coded for now, might become a parameter in the future.

		m_pBody->CreateFixture(&fixtureDef);
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

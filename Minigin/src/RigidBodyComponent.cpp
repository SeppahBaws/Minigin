#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "Physics.h"

#include <box2d/box2d.h>
#include <imgui.h>

#include "Renderer.h"

namespace dae
{
	RigidBodyComponent::RigidBodyComponent(const glm::vec2& size, RigidBodyType type)
		: m_Size(size), m_Type(type)
	{
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

		b2BodyDef bodyDef;
		bodyDef.type = bodyType;
		bodyDef.position.Set(objPos.x, objPos.y);
		m_pBody = Physics::GetInstance().GetWorld()->CreateBody(&bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(m_Size.x / 2, m_Size.y / 2);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f; // Hard-coded for now, might become a parameter in the future.

		m_pBody->CreateFixture(&fixtureDef);
	}

	void RigidBodyComponent::OnUpdate()
	{
		const b2Vec2 pos = m_pBody->GetPosition();
		m_pGameObject->GetTransform()->SetPosition(pos.x, pos.y);
	}

	void RigidBodyComponent::OnImGui()
	{
		const glm::vec2 objPos = GetGameObject()->GetTransform()->GetPosition();

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

		Renderer::GetInstance().DebugRenderRect(objPos, objPos + m_Size, c);
	}
}

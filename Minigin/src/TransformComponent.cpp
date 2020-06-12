#include "MiniginPCH.h"
#include "TransformComponent.h"

#include "GameObject.h"
#include "RigidBodyComponent.h"

namespace dae
{
	void TransformComponent::SetPosition(const glm::vec3& pos)
	{
		m_Position.x = pos.x;
		m_Position.y = pos.y;
		m_Position.z = pos.z;

		UpdatePhysicsBody();
	}

	// void TransformComponent::SetPositionRaw(const glm::vec3& pos)
	// {
	// 	m_Position.x = pos.x;
	// 	m_Position.y = pos.y;
	// 	m_Position.z = pos.z;
	// }

	void TransformComponent::Translate(const glm::vec2& movement)
	{
		Translate(glm::vec3(movement.x, movement.y, 0.0f));
	}

	void TransformComponent::Translate(const glm::vec3& movement)
	{
		m_Position.x += movement.x;
		m_Position.y += movement.y;
		m_Position.z += movement.z;

		UpdatePhysicsBody();
	}

	void TransformComponent::SetRotation(float rotation)
	{
		m_Rotation = rotation;

		UpdatePhysicsBody();
	}

	void TransformComponent::UpdatePhysicsBody()
	{
		RigidBodyComponent* pRB = GetGameObject()->GetComponent<RigidBodyComponent>();

		// When the position is changed during scene initialization, no RigidBodyComponent has been added yet.
		if (!pRB)
			return;

		pRB->UpdateBodyTransform(m_Position, m_Rotation);
	}
}

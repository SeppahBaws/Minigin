#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"

namespace dae
{
	void TransformComponent::SetPosition(const glm::vec3& pos)
	{
		m_Position.x = pos.x;
		m_Position.y = pos.y;
		m_Position.z = pos.z;

	}

	void TransformComponent::Translate(const glm::vec2& movement)
	{
		Translate(glm::vec3(movement.x, movement.y, 0.0f));
	}

	void TransformComponent::Translate(const glm::vec3& movement)
	{
		m_Position.x += movement.x;
		m_Position.y += movement.y;
		m_Position.z += movement.z;
	}

	void TransformComponent::SetRotation(float rotation)
	{
		m_Rotation = rotation;
	}
}

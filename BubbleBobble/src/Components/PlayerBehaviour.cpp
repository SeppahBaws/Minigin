#include "pch.h"
#include "PlayerBehaviour.h"

#include <Minigin/Scene/GameObject.h>

#include "Minigin/Core/Time.h"

#include <glm/glm.hpp>

namespace dae
{
	PlayerBehaviour::PlayerBehaviour()
		: m_MovementSpeed(150.0f)
	{
	}

	void PlayerBehaviour::OnUpdate()
	{
		const float dt = Time::GetDeltaTime();

		auto& input = InputManager::GetInstance();
		glm::vec3 pos = m_pGameObject->GetTransform()->GetPosition();
		
		const glm::vec2 movement = glm::vec2(input.GetAxis(GamepadAxis::LeftThumbX), -input.GetAxis(GamepadAxis::LeftThumbY));

		if (glm::length(movement) > 0.5f)
		{
			pos.x += movement.x * dt * m_MovementSpeed;
			pos.y += movement.y * dt * m_MovementSpeed;
		}

		m_pGameObject->GetTransform()->SetPosition(pos.x, pos.y, pos.z);
	}
}

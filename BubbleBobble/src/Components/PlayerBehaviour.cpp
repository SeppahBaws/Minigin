#include "pch.h"
#include "PlayerBehaviour.h"

#include <Minigin.h>

#include <glm/glm.hpp>

#include "imgui.h"

namespace dae
{
	PlayerBehaviour::PlayerBehaviour()
		: m_MovementSpeed(150.0f)
	{
	}

	void PlayerBehaviour::OnUpdate()
	{
		const float dt = Time::GetDeltaTime();

		InputManager& input = InputManager::GetInstance();
		glm::vec3 pos = m_pGameObject->GetTransform()->GetPosition();
		
		const glm::vec2 movement = glm::normalize(glm::vec2(
			input.GetAxis("MovementHorizontal"),
			input.GetAxis("MovementVertical"))
		);

		if (glm::length(movement) > 0.5f)
		{
			pos.x += movement.x * dt * m_MovementSpeed;
			pos.y += movement.y * dt * m_MovementSpeed;
		}

		m_pGameObject->GetTransform()->SetPosition(pos.x, pos.y, pos.z);

		if (input.GetAction("Shoot"))
		{
			std::cout << "Shoot!" << std::endl;
		}
	}

	void PlayerBehaviour::OnImGui()
	{
		if (ImGui::Begin("Test"))
		{
			ImGui::Text("Hello BubbleBobble!");

			if (ImGui::Button("Click me!"))
			{
				std::cout << "Hello there!" << std::endl;
			}
		}
		ImGui::End();

		if (ImGui::Begin("Test 2"))
		{
			ImGui::Text("I'm a second window! You can dock me in other windows!");
		}
		ImGui::End();
	}
}

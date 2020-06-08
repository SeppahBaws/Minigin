#include "pch.h"
#include "PlayerBehaviour.h"

#include "Time.h"
#include "InputManager.h"
#include "GameObject.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "imgui.h"
#include "RigidBodyComponent.h"

namespace dae
{
	PlayerBehaviour::PlayerBehaviour()
		: m_MovementSpeed(150.0f)
		, m_MovementForce(60.0f)
		, m_JumpForce(25.0f)
	{
	}

	void PlayerBehaviour::OnUpdate()
	{
		const float dt = Time::GetDeltaTime();
		
		InputManager& input = InputManager::GetInstance();
		RigidBodyComponent* pRB = m_pGameObject->GetComponent<RigidBodyComponent>();

		glm::vec2 movement = glm::vec2(
			input.GetAxis("MovementHorizontal"),
			0.0f
			// input.GetAxis("MovementVertical")
		);

		if (glm::length(movement) > 0.5f)
		{
			movement = glm::normalize(movement);
			// m_pGameObject->GetTransform()->Translate(movement * dt * m_MovementSpeed);
			pRB->ApplyForce(movement * m_MovementForce);
		}

		if (input.GetAction("Jump"))
		{
			printf("Jump!\n");
			pRB->ApplyImpulse({ 0.0f, -m_JumpForce });
		}
	}

	void PlayerBehaviour::OnImGui()
	{
		if (ImGui::Begin("Player Properties"))
		{
			const glm::vec3 pos = m_pGameObject->GetTransform()->GetPosition();
			ImGui::Text("Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);

			ImGui::SliderFloat("Movement Force", &m_MovementForce, 0.0f, 200.0f);
			ImGui::SliderFloat("Jump Force", &m_JumpForce, 0.0f, 100.0f);

			ImGui::Spacing();

			InputManager& input = InputManager::GetInstance();

			const float x = input.GetAxis("MovementHorizontal");
			const float y = input.GetAxis("MovementVertical");

			ImGui::Text("movement: (%.2f, %.2f)", x, y);

			const bool w = input.GetKeyState(Key::W) == InputState::Down;
			const bool a = input.GetKeyState(Key::A) == InputState::Down;
			const bool s = input.GetKeyState(Key::S) == InputState::Down;
			const bool d = input.GetKeyState(Key::D) == InputState::Down;

			ImGui::Text("W: %d", w);
			ImGui::Text("A: %d", a);
			ImGui::Text("S: %d", s);
			ImGui::Text("D: %d", d);

			InputState state = input.GetKeyState(Key::Space);

			switch (state)
			{
			case InputState::Pressed:
				ImGui::Text("Space: Pressed");
				break;
			case InputState::Released:
				ImGui::Text("Space: Released");
				break;
			case InputState::Down:
				ImGui::Text("Space: Down");
				break;
			case InputState::Up:
				ImGui::Text("Space: Up");
				break;
			}

			ImGui::Spacing();

			if (ImGui::Button("ResetPlayer"))
			{
				m_pGameObject->GetTransform()->SetPosition({ 200, 200, 0 });
			}
		}
		ImGui::End();
	}
}

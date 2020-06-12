#include "pch.h"
#include "PlayerBehaviour.h"

#include "Time.h"
#include "InputManager.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"

#include "imgui.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

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

		glm::vec2 movement = glm::vec2(input.GetAxis("MovementHorizontal"), 0.0f);

		if (glm::length(movement) > 0.5f)
		{
			movement = glm::normalize(movement);
			pRB->ApplyForce(movement * m_MovementForce);
		}

		if (input.GetAction("Jump"))
		{
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

			if (ImGui::Button("ResetPlayer"))
			{
				m_pGameObject->GetTransform()->SetPosition({ 200, 200, 0 });
			}
		}
		ImGui::End();
	}
}

#include "pch.h"
#include "MainMenuManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TextComponent.h"

#include <imgui.h>

void MainMenuManager::AddButton(Button* button)
{
	m_Buttons.push_back(button);
}

void MainMenuManager::RegisterSpritePrompt(dae::GameObject* object)
{
	m_pSpritePrompt = object;
}

void MainMenuManager::OnPrepare()
{
	m_Buttons[0]->GetGameObject()->GetComponent<dae::TextComponent>()->SetColor(m_ActiveColor);
}

void MainMenuManager::OnUpdate()
{
	using namespace dae;
	if (InputManager::GetInstance().GetAction("MainMenu_SelectNext"))
	{
		if (m_SelectedIdx < m_Buttons.size() - 1)
		{
			m_Buttons[m_SelectedIdx]->GetGameObject()->GetComponent<TextComponent>()->SetColor(m_InactiveColor);
			m_SelectedIdx++;
			m_Buttons[m_SelectedIdx]->GetGameObject()->GetComponent<TextComponent>()->SetColor(m_ActiveColor);

			glm::vec3 pos = m_pSpritePrompt->GetTransform()->GetPosition();
			pos.y = m_Buttons[m_SelectedIdx]->GetGameObject()->GetTransform()->GetPosition().y;
			m_pSpritePrompt->GetTransform()->SetPosition(pos);
		}
	}

	if (InputManager::GetInstance().GetAction("MainMenu_SelectPrevious"))
	{
		if (m_SelectedIdx > 0)
		{
			m_Buttons[m_SelectedIdx]->GetGameObject()->GetComponent<TextComponent>()->SetColor(m_InactiveColor);
			m_SelectedIdx--;
			m_Buttons[m_SelectedIdx]->GetGameObject()->GetComponent<TextComponent>()->SetColor(m_ActiveColor);

			glm::vec3 pos = m_pSpritePrompt->GetTransform()->GetPosition();
			pos.y = m_Buttons[m_SelectedIdx]->GetGameObject()->GetTransform()->GetPosition().y;
			m_pSpritePrompt->GetTransform()->SetPosition(pos);
		}
	}

	if (InputManager::GetInstance().GetAction("MainMenu_Activate"))
	{
		m_Buttons[m_SelectedIdx]->Execute();
	}
}

void MainMenuManager::OnImGui()
{
	if (ImGui::Begin("Main menu manager"))
	{
		ImGui::Text("Registered buttons: %d", m_Buttons.size());
		ImGui::Text("Current selected: %d", m_SelectedIdx);
	}
	ImGui::End();
}

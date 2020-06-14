#include "pch.h"
#include "GameOverManager.h"

#include "InputManager.h"
#include "SceneManager.h"

void GameOverManager::OnUpdate()
{
	if (dae::InputManager::GetInstance().GetAction("MainMenu_Activate"))
	{
		dae::SceneManager::GetInstance().ActivateScene("MainMenu");
	}
}

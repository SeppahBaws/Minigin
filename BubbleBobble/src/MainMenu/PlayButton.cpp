#include "pch.h"
#include "PlayButton.h"

#include "SceneManager.h"

void PlayButton::Execute()
{
	dae::SceneManager::GetInstance().ActivateScene("Game");
}

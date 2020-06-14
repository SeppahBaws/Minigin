#include "pch.h"
#include "GameManager.h"

#include "SceneManager.h"
#include "Observer/Events.h"

void GameManager::OnNotify(const dae::GameObject&, Event event)
{
	switch (event)
	{
	case Event::PlayerLoseLife:
		m_Lives--;
		if (m_Lives < 0)
		{
			dae::SceneManager::GetInstance().ActivateScene("GameOver");
		}
		break;
	}
}

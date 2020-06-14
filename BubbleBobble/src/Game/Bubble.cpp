#include "pch.h"
#include "Bubble.h"
#include "GameObject.h"

#include "EntityTags.h"
#include "Time.h"
#include "Scene.h"

Bubble::Bubble()
{
	m_StateTimings = {
		{ BubbleState::Shoot, 1.0f },
		{ BubbleState::Idle, 4.0f },
		{ BubbleState::Pop, 4.5f }
	};
	m_TotalTime = m_StateTimings[BubbleState::Pop];
}

void Bubble::OnPrepare()
{
	m_pSprite = GetGameObject()->GetComponent<dae::SpriteComponent>();
}

void Bubble::OnUpdate()
{
	using namespace dae;

	const float dt = Time::GetDeltaTime();
	m_Timer += dt;

	if (m_Timer >= m_StateTimings[m_CurrentState])
	{
		m_CurrentState = (BubbleState)((int)m_CurrentState + 1);

		switch (m_CurrentState)
		{
		case BubbleState::Shoot:
			m_pSprite->UpdateSprite("sprites/bubble_shoot.png", 1, 2, 3, 4);
			break;
		case BubbleState::Idle:
			m_pSprite->UpdateSprite("sprites/bubble_idle.png", 1, 1, 3, 0);
			break;
		case BubbleState::Pop:
			m_pSprite->UpdateSprite("sprites/bubble_pop.png", 1, 2, 3, 4);
			break;
		default: ;
		}
	}

	if (m_Timer >= m_TotalTime)
	{
		GetGameObject()->GetScene()->Remove(GetGameObject());
	}
}

void Bubble::OnCollisionBegin(dae::GameObject* object)
{
	std::cout << "AAAAAAAAAAAH BUBBLE COLLISION!!!!" << std::endl;

	switch (object->GetTag())
	{
	case EntityTags::ET_Enemy:
		std::cout << "Time to put this entity in a bubble!" << std::endl;
		break;
	default:
		break;
	}
}

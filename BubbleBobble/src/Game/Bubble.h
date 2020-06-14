#pragma once
#include "BaseComponent.h"
#include "SpriteComponent.h"

enum class BubbleState
{
	Shoot = 0,
	Idle,
	Pop
};

class Bubble final : public dae::BaseComponent
{
public:
	Bubble();

	void OnPrepare() override;
	void OnUpdate() override;
	void OnCollisionBegin(dae::GameObject* object) override;

private:
	std::unordered_map<BubbleState, float> m_StateTimings;
	BubbleState m_CurrentState = BubbleState::Shoot;
	float m_Timer = 0.0f;
	float m_TotalTime;

	dae::SpriteComponent* m_pSprite = nullptr;
};

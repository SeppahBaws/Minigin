#pragma once
#include "BaseComponent.h"
#include "RigidBodyComponent.h"

class ZenChanBehaviour : public dae::BaseComponent
{
public:
	void OnPrepare() override;
	void OnUpdate() override;

private:
	const float m_StateTimeout = 1.0f;
	float m_StateTimer = 0.0f;

	glm::vec2 m_MovementForce = { 60, 0 };

	dae::RigidBodyComponent* m_pRB = nullptr;
};

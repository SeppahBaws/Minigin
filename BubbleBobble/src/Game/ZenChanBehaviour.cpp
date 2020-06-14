#include "pch.h"
#include "ZenChanBehaviour.h"

#include "Time.h"
#include "GameObject.h"

void ZenChanBehaviour::OnPrepare()
{
	m_pRB = GetGameObject()->GetComponent<dae::RigidBodyComponent>();
}

void ZenChanBehaviour::OnUpdate()
{
	const float dt = dae::Time::GetDeltaTime();

	m_StateTimer += dt;

	if (m_StateTimer >= m_StateTimeout)
	{
		m_StateTimer = 0.0f;

		m_MovementForce.x *= -1.0f;
	}

	m_pRB->ApplyForce(m_MovementForce);
}

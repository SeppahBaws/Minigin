#include "MiniginPCH.h"
#include "ColliderComponent.h"

// #include <box2d/box2d.h>
// #include "Physics.h"
// #include "PhysicsConvert.h"

namespace dae
{
	ColliderComponent::ColliderComponent(const glm::vec2& offset, const glm::vec2& size, bool isTrigger)
		: m_Offset(offset)
		, m_Size(size)
		, m_IsTrigger(isTrigger)
	{
	}

	// b2FixtureDef ColliderComponent::GetFixtureDef() const
	// {
	// 	const float ppm = Physics::GetInstance().GetPPMRatio();
	//
	// 	b2PolygonShape shape;
	// 	shape.SetAsBox((m_Size.x / 2) / ppm, (m_Size.y / 2) / ppm);
	// 	// shape.SetAsBox((m_Size.x / 2) / ppm, (m_Size.y / 2) / ppm, PhysicsConvert::ToBox2DVec(m_Offset), 0.0f);
	//
	// 	b2FixtureDef fixtureDef;
	// 	fixtureDef.shape = &shape;
	// 	fixtureDef.density = m_IsTrigger ? 0.0f : 1.0f;
	// 	fixtureDef.isSensor = m_IsTrigger;
	// 	// fixtureDef.userData = GetGameObject();
	// 	fixtureDef.friction = 0.5f; // Hard-coded for now, might become a parameter in the future.
	//
	// 	return fixtureDef;
	// }
}

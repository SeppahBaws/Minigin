#include "MiniginPCH.h"
#include "Physics.h"

namespace dae
{
	void Physics::Init()
	{
		const b2Vec2 gravity(0.0f, 9.81f);
		m_pWorld = new b2World(gravity);
	}

	void Physics::Destroy()
	{
		delete m_pWorld;
	}

	void Physics::Update()
	{
		const float timeStep = 1.0f / 60.0f;
		const int velocityIterations = 8;
		const int positionIterations = 3;

		m_pWorld->Step(timeStep, velocityIterations, positionIterations);
	}
}

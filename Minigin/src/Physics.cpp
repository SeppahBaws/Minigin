#include "MiniginPCH.h"
#include "Physics.h"

namespace dae
{
	void Physics::Update(b2World* pWorld)
	{
		const float timeStep = 1.0f / 60.0f;
		const int velocityIterations = 8;
		const int positionIterations = 3;

		pWorld->Step(timeStep, velocityIterations, positionIterations);
	}

	b2World* Physics::CreateWorld() const
	{
		const b2Vec2 gravity(0.0f, 9.81f);
		return new b2World(gravity);
	}
}

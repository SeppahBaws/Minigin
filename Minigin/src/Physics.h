#pragma once
#include "Singleton.h"

#include <box2d/box2d.h>

namespace dae
{
	class Physics final : public Singleton<Physics>
	{
	public:
		Physics() = default;

		void Update(b2World* pWorld);

		b2World* CreateWorld() const;
		float GetPPMRatio() const { return m_PPMRatio; }

	private:
		const float m_PPMRatio = 32.f; // Pixels Per Meter ratio. Box2d works in meters, so we'll need to convert.
	};
}

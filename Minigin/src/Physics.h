﻿#pragma once
#include "Singleton.h"

#include <box2d/box2d.h>

#pragma warning(push)
#pragma warning(disable:4201)
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Physics final : public Singleton<Physics>
	{
	public:
		Physics() = default;

		void Init();
		void Destroy();
		void Update();

		b2World* GetWorld() const { return m_pWorld; }
		float GetPPMRatio() const { return m_PPMRatio; }

	private:
		b2World* m_pWorld;
		const float m_PPMRatio = 32.f; // Pixels Per Meter ratio. Box2d works in meters, so we'll need to convert.
	};
}

#pragma once
#include "Singleton.h"

#include <box2d/box2d.h>

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

	private:
		b2World* m_pWorld;
	};
}

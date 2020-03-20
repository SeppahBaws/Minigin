#pragma once
#include "../Utils/Singleton.h"
#include <chrono>

namespace dae
{
	class Time : public Singleton<Time>
	{
	public:
		static std::chrono::high_resolution_clock::time_point GetTime();

		static float GetDeltaTime();
		static void SetDeltaTime(float deltaTime);

		void Update(std::chrono::high_resolution_clock::time_point lastTime);

	private:
		static float m_DeltaTime;
		static std::chrono::high_resolution_clock::time_point m_StartTime;
	};
}

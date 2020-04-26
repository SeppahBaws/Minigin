#pragma once
#include <SDL.h>

#include "Singleton.h"

namespace dae
{
	class ImGuiWrapper : public Singleton<ImGuiWrapper>
	{
	public:
		static void Init(SDL_Window* window);
		static void Destroy();

		static void HandleEvents(SDL_Event e);
		static void NewFrame();
		static void Render();
	};
}

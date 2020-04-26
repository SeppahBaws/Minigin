#pragma once

#include <SDL_mouse.h>

namespace dae
{
	enum class MouseButton
	{
		Left	= SDL_BUTTON_LMASK,
		Right	= SDL_BUTTON_RMASK,
		Middle	= SDL_BUTTON_MMASK,
		Back	= SDL_BUTTON_X1MASK,
		Forward	= SDL_BUTTON_X2MASK
	};

	enum class MouseAxis
	{
		X,
		Y,
		Scroll
	};
}

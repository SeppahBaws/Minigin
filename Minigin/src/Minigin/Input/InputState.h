#pragma once

namespace dae
{
	enum class InputState
	{
		/* The input is going from released to pressed this frame */
		Pressed,

		/* The input is going from pressed to released this frame */
		Released,

		/* The input is being held down (a.k.a. it's active) */
		Down,

		/* The input is being held up (a.k.a. it's inactive) */
		Up
	};
}

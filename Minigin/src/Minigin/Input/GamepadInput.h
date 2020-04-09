#pragma once

#include <Xinput.h>

#include <Windows.h>

namespace dae
{
	enum class GamepadButton
	{
		DPadUp			= XINPUT_GAMEPAD_DPAD_UP,
		DPadDown		= XINPUT_GAMEPAD_DPAD_DOWN,
		DPadLeft		= XINPUT_GAMEPAD_DPAD_LEFT,
		DPadRight		= XINPUT_GAMEPAD_DPAD_RIGHT,
		Start			= XINPUT_GAMEPAD_START,
		Back			= XINPUT_GAMEPAD_BACK,
		LeftThumb		= XINPUT_GAMEPAD_LEFT_THUMB,
		RightThumb		= XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftShoulder	= XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightSHOULDER	= XINPUT_GAMEPAD_RIGHT_SHOULDER,
		A				= XINPUT_GAMEPAD_A,
		B				= XINPUT_GAMEPAD_B,
		X				= XINPUT_GAMEPAD_X,
		Y				= XINPUT_GAMEPAD_Y
	};

	enum class GamepadAxis
	{
		LeftTrigger,
		RightTrigger,
		LeftThumbX,
		LeftThumbY,
		RightThumbX,
		RightThumbY
	};
}

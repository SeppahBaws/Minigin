#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

namespace dae
{
	bool InputManager::ProcessInput()
	{
		m_PreviousGamepadState = m_CurrentGamepadState;
		ZeroMemory(&m_CurrentGamepadState, sizeof(XINPUT_STATE));
		XInputGetState(0, &m_CurrentGamepadState);

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return false;
			}
			if (e.type == SDL_KEYDOWN) {
			
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
			
			}
		}

		return true;
	}

	bool InputManager::IsPressed(GamepadButton button) const
	{
		return m_CurrentGamepadState.Gamepad.wButtons& WORD(button)
			&& !(m_PreviousGamepadState.Gamepad.wButtons & WORD(button));
	}

	bool InputManager::IsReleased(GamepadButton button) const
	{
		return !(m_CurrentGamepadState.Gamepad.wButtons & WORD(button))
			&& m_PreviousGamepadState.Gamepad.wButtons & WORD(button);
	}

	bool InputManager::GetButton(GamepadButton button) const
	{
		return m_CurrentGamepadState.Gamepad.wButtons & WORD(button);
	}

	float InputManager::GetAxis(GamepadAxis axis) const
	{
		switch (axis)
		{
		case GamepadAxis::LeftTrigger:		return float(m_CurrentGamepadState.Gamepad.bLeftTrigger) / 255.0f;
		case GamepadAxis::RightTrigger:		return float(m_CurrentGamepadState.Gamepad.bRightTrigger) / 255.0f;
		case GamepadAxis::LeftThumbX:		return float(m_CurrentGamepadState.Gamepad.sThumbLX) / 32767.0f;
		case GamepadAxis::LeftThumbY:		return float(m_CurrentGamepadState.Gamepad.sThumbLY) / 32767.0f;
		case GamepadAxis::RightThumbX:		return float(m_CurrentGamepadState.Gamepad.sThumbRX) / 32767.0f;
		case GamepadAxis::RightThumbY:		return float(m_CurrentGamepadState.Gamepad.sThumbRY) / 32767.0f;
		default: return 0;
		}
	}
	
}

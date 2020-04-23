#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

namespace dae
{
	bool InputManager::ProcessInput()
	{
		m_PreviousGamepadState = m_CurrentGamepadState;
		m_PreviousKeyboardState = m_CurrentKeyboardState;
		m_PreviousMouseButtonState = m_CurrentMouseButtonState;

		ZeroMemory(&m_CurrentGamepadState, sizeof(XINPUT_STATE));
		XInputGetState(0, &m_CurrentGamepadState);

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				return false;

			case SDL_KEYDOWN:
				m_CurrentKeyboardState.SetState(e.key.keysym.scancode, true);
				break;
			case SDL_KEYUP:
				m_CurrentKeyboardState.SetState(e.key.keysym.scancode, false);
				break;

			case SDL_MOUSEMOTION:
				// TODO
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_CurrentMouseButtonState |= SDL_BUTTON(e.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				m_CurrentMouseButtonState &= ~SDL_BUTTON(e.button.button);
				break;
			case SDL_MOUSEWHEEL:
				// TODO
				break;

			default:
				break;
			}
		}

		return true;
	}

	void InputManager::SetupAxis(const std::string& name, const InputBinding& axisBinding)
	{
		if (m_Bindings.count(name) > 0)
		{
			std::cerr << "Cannot assign input axis binding, a binding with name '" << name << "' already exists!" << std::endl;
			return;
		}
		
		m_Bindings[name] = axisBinding;
	}

	void InputManager::SetupAction(const std::string& name, const InputBinding& actionBinding)
	{
		if (m_Bindings.count(name) > 0)
		{
			std::cerr << "Cannot assign input action binding, a binding with name '" << name << "' already exists!" << std::endl;
			return;
		}

		m_Bindings[name] = actionBinding;
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
		case GamepadAxis::LeftTrigger:		return float(m_CurrentGamepadState.Gamepad.bLeftTrigger)  / GAMEPAD_TRIGGER_MAX;
		case GamepadAxis::RightTrigger:		return float(m_CurrentGamepadState.Gamepad.bRightTrigger) / GAMEPAD_TRIGGER_MAX;
		case GamepadAxis::LeftThumbX:		return float(m_CurrentGamepadState.Gamepad.sThumbLX) / GAMEPAD_AXIS_MAX;
		case GamepadAxis::LeftThumbY:		return float(m_CurrentGamepadState.Gamepad.sThumbLY) / GAMEPAD_AXIS_MAX;
		case GamepadAxis::RightThumbX:		return float(m_CurrentGamepadState.Gamepad.sThumbRX) / GAMEPAD_AXIS_MAX;
		case GamepadAxis::RightThumbY:		return float(m_CurrentGamepadState.Gamepad.sThumbRY) / GAMEPAD_AXIS_MAX;
		default: return 0;
		}
	}


	InputState InputManager::GetButtonState(GamepadButton button) const
	{
		const bool prevFrame = m_PreviousGamepadState.Gamepad.wButtons & WORD(button);
		const bool currFrame = m_CurrentGamepadState.Gamepad.wButtons & WORD(button);

		if (!prevFrame && !currFrame)
			return InputState::Up;
		if (!prevFrame && currFrame)
			return InputState::Pressed;
		if (prevFrame && currFrame)
			return InputState::Down;
		if (prevFrame && !currFrame)
			return InputState::Released;

		std::cout << "ERROR: no valid InputState found for the current gamepad state!" << std::endl;
		return InputState::Up;
	}

	InputState InputManager::GetButtonState(MouseButton button) const
	{
		const bool prevFrame = m_PreviousMouseButtonState & uint8_t(button);
		const bool currFrame = m_CurrentMouseButtonState & uint8_t(button);

		if (!prevFrame && !currFrame)
			return InputState::Up;
		if (!prevFrame && currFrame)
			return InputState::Pressed;
		if (prevFrame && currFrame)
			return InputState::Down;
		if (prevFrame && !currFrame)
			return InputState::Released;

		std::cout << "ERROR: no valid InputState found for the current mouse button state!" << std::endl;
		return InputState::Up;
	}

	InputState InputManager::GetKeyState(Key key) const
	{
		const bool prevFrame = m_PreviousKeyboardState.Evaluate(uint64_t(key));
		const bool currFrame = m_CurrentKeyboardState.Evaluate(uint64_t(key));

		if (!prevFrame && !currFrame)
			return InputState::Up;
		if (!prevFrame && currFrame)
			return InputState::Pressed;
		if (prevFrame && currFrame)
			return InputState::Down;
		if (prevFrame && !currFrame)
			return InputState::Released;

		std::cout << "ERROR: no valid InputState found for the current keyboard state!" << std::endl;
		return InputState::Up;
	}

	float InputManager::GetAxis(const std::string& name)
	{
		return m_Bindings[name].EvaluateAxis();
	}

	bool InputManager::GetAction(const std::string& name)
	{
		return m_Bindings[name].EvaluateAction();
	}
}

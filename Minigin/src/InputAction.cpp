#include "MiniginPCH.h"
#include "InputAction.h"

#include "InputManager.h"

namespace dae
{
	InputAction::InputAction(GamepadButton button, InputState state)
	{
		m_GamepadButton = button;
		m_State = state;
		m_Type = BindingType::Gamepad;
	}

	InputAction::InputAction(Key key, InputState state)
	{
		m_KeyboardKey = key;
		m_State = state;
		m_Type = BindingType::Keyboard;
	}

	InputAction::InputAction(MouseButton button, InputState state)
	{
		m_MouseButton = button;
		m_State = state;
		m_Type = BindingType::Mouse;
	}

	bool InputAction::Evaluate() const
	{
		switch (m_Type)
		{
		case BindingType::Unset:
			std::cout << "ERROR: InputAction is Unset, cannot evaluate InputAction!" << std::endl;
			return false;

		case BindingType::Gamepad:
			return InputManager::GetInstance().GetButtonState(m_GamepadButton) == m_State;

		case BindingType::Keyboard:
			return InputManager::GetInstance().GetKeyState(m_KeyboardKey) == m_State;

		case BindingType::Mouse:
			return InputManager::GetInstance().GetButtonState(m_MouseButton) == m_State;
		}

		return false;
	}
}

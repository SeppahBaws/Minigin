#include "MiniginPCH.h"
#include "InputAxis.h"

#include "InputManager.h"

namespace dae
{
	InputAxis::InputAxis(GamepadAxis axis, float strength)
	{
		m_GamepadAxis = axis;
		m_Strength = strength;

		m_Type = BindingType::Gamepad;
	}

	InputAxis::InputAxis(Key key, float strength)
	{
		m_Key = key;
		m_Strength = strength;

		m_Type = BindingType::Keyboard;
	}

	float InputAxis::Evaluate() const
	{
		float amount = 0.0f;
		switch (m_Type)
		{
		case BindingType::Unset:
			std::cerr << "ERROR: InputAxis is Unset, cannot evaluate InputAxis!" << std::endl;
			return 0.0f;

		case BindingType::Gamepad:
			amount = InputManager::GetInstance().GetAxis(m_GamepadAxis);
			if (amount != 0.0f)
			{
				return amount * m_Strength;
			}
			return 0.0f;

		case BindingType::Keyboard:
			const bool activated = InputManager::GetInstance().GetKeyState(m_Key) == InputState::Down ||
				InputManager::GetInstance().GetKeyState(m_Key) == InputState::Pressed;

			return activated ? m_Strength : 0.0f;
		}

		return 0.0f;
	}
}

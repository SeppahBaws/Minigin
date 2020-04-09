#pragma once
#include "../Utils/Singleton.h"

#include "GamepadInput.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		/**
		 * Returns true if the gamepad button is being pressed *this frame*.
		 */
		bool IsPressed(GamepadButton button) const;

		/**
		 * Returns true if the gamepad button is being released *this frame*.
		 */
		bool IsReleased(GamepadButton button) const;

		/**
		 * Returns whether the gamepad button is currently being pressed or not.
		 */
		bool GetButton(GamepadButton button) const;

		/**
		 * Returns the value of the gamepad axis.
		 */
		float GetAxis(GamepadAxis axis) const;

	private:
		XINPUT_STATE m_CurrentGamepadState{};
		XINPUT_STATE m_PreviousGamepadState{};
	};

}

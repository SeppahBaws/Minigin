#pragma once
#include <SDL.h>

#include "Singleton.h"

#include "InputState.h"

#include "GamepadInput.h"
#include "KeyboardInput.h"
#include "MouseInput.h"

#include "KeyboardState.h"

#include "InputBinding.h"

#define GAMEPAD_TRIGGER_MAX 255.0f;
#define GAMEPAD_AXIS_MAX  32767.0f;

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		void ProcessInput(const SDL_Event& e);

		void SetupAxis(const std::string& name, const InputBinding& axisBinding);
		void SetupAction(const std::string& name, const InputBinding& actionBinding);

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

		float GetAxis(const std::string& name);
		bool GetAction(const std::string& name);

		InputState GetButtonState(GamepadButton button) const;
		InputState GetButtonState(MouseButton button) const;
		InputState GetKeyState(Key key) const;

	private:
		XINPUT_STATE m_CurrentGamepadState{};
		XINPUT_STATE m_PreviousGamepadState{};

		KeyboardState m_CurrentKeyboardState;
		KeyboardState m_PreviousKeyboardState;

		uint8_t m_CurrentMouseButtonState = 0;
		uint8_t m_PreviousMouseButtonState = 0;

		std::unordered_map<std::string, InputBinding> m_Bindings;
	};

}

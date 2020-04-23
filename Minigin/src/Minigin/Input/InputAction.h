#pragma once

namespace dae
{
	enum class MouseButton;
	enum class Key;
	enum class InputState;
	enum class GamepadButton;

	class InputAction
	{
	public:
		InputAction(GamepadButton button, InputState state);
		InputAction(Key key, InputState state);
		InputAction(MouseButton button, InputState state);

		bool Evaluate() const;

	private:
		enum class BindingType
		{
			Unset,
			Gamepad,
			Keyboard,
			Mouse
		};

	private:
		GamepadButton m_GamepadButton;
		Key m_KeyboardKey;
		MouseButton m_MouseButton;

		InputState m_State;

		BindingType m_Type = BindingType::Unset;
	};
}

#pragma once

#include "GamepadInput.h"
#include "KeyboardInput.h"

namespace dae
{
	class InputAxis
	{
	public:
		InputAxis(GamepadAxis axis, float strength);
		InputAxis(Key key, float strength);

		float Evaluate() const;

	private:
		enum class BindingType
		{
			Unset,
			Gamepad,
			Keyboard
		};

	private:
		GamepadAxis m_GamepadAxis;
		Key m_Key;
		float m_Strength;

		BindingType m_Type = BindingType::Unset;
	};
}

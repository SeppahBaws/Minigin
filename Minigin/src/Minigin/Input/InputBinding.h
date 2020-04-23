#pragma once

#include "InputAxis.h"
#include "InputAction.h"

namespace dae
{
	class InputBinding
	{
	public:
		InputBinding() = default;
		InputBinding(const std::vector<InputAxis>& axises);
		InputBinding(const std::vector<InputAction>& actions);

		float EvaluateAxis();
		bool EvaluateAction();

	private:
		enum class BindingType
		{
			Unset,
			Axis,
			Action
		};

	private:
		std::vector<InputAxis> m_AxisBindings;
		std::vector<InputAction> m_ActionBindings;

		BindingType m_Type;
	};
}

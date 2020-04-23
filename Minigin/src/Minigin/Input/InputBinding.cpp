#include "MiniginPCH.h"
#include "InputBinding.h"

namespace dae
{
	InputBinding::InputBinding(const std::vector<InputAxis>& axises)
	{
		m_AxisBindings = axises;
		m_Type = BindingType::Axis;
	}

	InputBinding::InputBinding(const std::vector<InputAction>& actions)
	{
		m_ActionBindings = actions;
		m_Type = BindingType::Action;
	}

	float InputBinding::EvaluateAxis()
	{
		if (m_Type != BindingType::Axis)
		{
			std::cout << "ERROR: EvaluateAxis() called for a binding that's not and axis binding!" << std::endl;
			return 0.0f;
		}

		float value = 0.0f;
		for (InputAxis& axis : m_AxisBindings)
		{
			value = axis.Evaluate();
			if (value != 0.0f)
				return value;
		}

		return value;
	}

	bool InputBinding::EvaluateAction()
	{
		if (m_Type != BindingType::Action)
		{
			std::cout << "ERROR: EvaluateAction() called for a binding that's not and action binding!" << std::endl;
			return false;
		}

		bool isTriggered = false;
		for (InputAction& action : m_ActionBindings)
		{
			isTriggered = action.Evaluate();
			if (isTriggered)
				break;
		}

		return isTriggered;
	}
}

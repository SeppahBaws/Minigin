#pragma once
#include "BaseComponent.h"

class Button : public dae::BaseComponent
{
public:
	virtual ~Button() = default;

	virtual void Execute() = 0;
};

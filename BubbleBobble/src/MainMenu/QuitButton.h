#pragma once
#include "Button.h"

class QuitButton final : public Button
{
public:
	virtual ~QuitButton() = default;

	void Execute() override;
};

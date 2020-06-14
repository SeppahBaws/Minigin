#pragma once
#include "Button.h"

class PlayButton final : public Button
{
public:
	virtual ~PlayButton() = default;

	void Execute() override;
};

#pragma once

#include "MiniginApp.h"

class BubbleBobble final : public dae::MiniginApp
{
public:
	BubbleBobble() = default;
	virtual ~BubbleBobble() = default;

	void LoadGame() const override;

private:
	void SetupInput() const;
	void SetupScene() const;
};

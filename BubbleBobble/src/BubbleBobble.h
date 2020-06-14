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

	enum EntityTags : int
	{
		Player	= 0,
		Enemy	= 1,
		Ground	= 2,
		Wall	= 3
	};
};

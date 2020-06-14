#pragma once
#include "BaseComponent.h"
#include "Observer/Observer.h"

class GameManager final : public dae::BaseComponent, public Observer
{
public:
	
	void OnNotify(const dae::GameObject& object, Event event) override;

private:
	int m_Lives = 4;
};

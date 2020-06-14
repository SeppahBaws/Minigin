#pragma once
#include "BaseComponent.h"
#include "Observer/Observer.h"

namespace dae
{
	class TextComponent;
}

class LivesDisplay final : public dae::BaseComponent, public Observer
{
public:

	void OnPrepare() override;
	void OnUpdate();

	void OnNotify(const dae::GameObject& object, Event event) override;

private:
	int m_Lives = 4;

	dae::TextComponent* m_pText = nullptr;
};

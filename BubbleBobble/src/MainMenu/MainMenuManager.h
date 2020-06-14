#pragma once
#include "BaseComponent.h"
#include "Button.h"
#include "Color.h"

class MainMenuManager final : public dae::BaseComponent
{
public:
	void AddButton(Button* button);

	void OnPrepare() override;
	void OnUpdate() override;
	void OnImGui() override;

private:
	std::vector<Button*> m_Buttons;
	size_t m_SelectedIdx;

	const dae::Color m_ActiveColor = dae::Color(1.0f, 0.0f, 0.0f);
	const dae::Color m_InactiveColor = dae::Color(1.0f, 1.0f, 1.0f);
};

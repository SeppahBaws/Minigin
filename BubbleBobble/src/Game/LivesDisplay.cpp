#include "pch.h"
#include "LivesDisplay.h"
#include "GameObject.h"
#include "TextComponent.h"

#include "Observer/Events.h"


void LivesDisplay::OnPrepare()
{
	m_pText = GetGameObject()->GetComponent<dae::TextComponent>();
	if (!m_pText)
		std::cerr << "ERROR: no TextComponent was attached to the LivesDisplay GameObject!" << std::endl;
}

void LivesDisplay::OnUpdate()
{
	if (!m_pText)
		return;

	std::stringstream ss;
	ss << "lives: " << m_Lives;
	m_pText->SetText(ss.str());
}

void LivesDisplay::OnNotify(const dae::GameObject&, Event event)
{
	switch (event)
	{
	case Event::PlayerLoseLife:
		m_Lives--;
		break;
	default:
		break;
	}
}

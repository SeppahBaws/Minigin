#include "pch.h"

#include "FPSComponent.h"
#include "Time.h"
#include "GameObject.h"
#include "Components.h"

namespace dae
{
	FPSComponent::FPSComponent()
	{
	}

	FPSComponent::~FPSComponent()
	{
	}

	void FPSComponent::OnUpdate()
	{
		std::stringstream ss;
		ss << int(1.0f / Time::GetDeltaTime());
		ss << " fps";
		m_pGameObject->GetComponent<TextComponent>()->SetText(ss.str());
	}
}

#pragma once
#include "BaseComponent.h"

namespace dae
{
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent();
		~FPSComponent();
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;

		void OnUpdate() override;
	};
}

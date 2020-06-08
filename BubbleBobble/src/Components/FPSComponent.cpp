#include "pch.h"

#include "FPSComponent.h"
#include "Time.h"
#include "imgui.h"

namespace dae
{
	FPSComponent::FPSComponent()
	{
	}

	FPSComponent::~FPSComponent()
	{
	}

	void FPSComponent::OnImGui()
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 window_pos = ImVec2(viewport->Pos.x + 10.0f, viewport->Pos.y + 10.0f);
		ImVec2 window_pos_pivot = ImVec2(0.0f, 0.0f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::SetNextWindowBgAlpha(0.35f);

		if (ImGui::Begin("Statistics", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
		{
			ImGui::Text("Application Statistics");
			ImGui::Separator();
			ImGui::Text("FPS: %.2f", 1.0f / Time::GetDeltaTime());
			ImGui::Text("Frame time: %.5f ms", Time::GetDeltaTime());

		}
		ImGui::End();
	}

}

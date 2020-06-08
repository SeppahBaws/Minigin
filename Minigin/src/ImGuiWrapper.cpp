#include "MiniginPCH.h"
#include "ImGuiWrapper.h"

#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Time.h"

namespace dae
{
	void ImGuiWrapper::Init(SDL_Window* window)
	{
		int width, height;
		SDL_GetWindowSize(window, &width, &height);

		ImGui::CreateContext();
		ImGuiSDL::Initialize(Renderer::GetInstance().GetSDLRenderer(), width, height);

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	}

	void ImGuiWrapper::Destroy()
	{
		ImGuiSDL::Deinitialize();
		ImGui::DestroyContext();
	}

	void ImGuiWrapper::HandleEvents(SDL_Event e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int scrollWheel = 0;

		switch (e.type)
		{
		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				io.DisplaySize.x = static_cast<float>(e.window.data1);
				io.DisplaySize.y = static_cast<float>(e.window.data2);
			}
			break;

		case SDL_MOUSEWHEEL:
			scrollWheel = e.wheel.y;
			break;

		default:
			break;
		}

		int mouseX, mouseY;
		const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

		io.DeltaTime = Time::GetDeltaTime();
		io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
		io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
		io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
		io.MouseWheel = static_cast<float>(scrollWheel);
		io.WantCaptureKeyboard = true;
		io.WantCaptureMouse = true;
	}

	void ImGuiWrapper::NewFrame()
	{
		ImGui::NewFrame();
	}

	void ImGuiWrapper::Render()
	{
		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			SDL_Window* backupWindow = SDL_GL_GetCurrentWindow();
			SDL_GLContext backupContext = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(backupWindow, backupContext);
		}
	}
}

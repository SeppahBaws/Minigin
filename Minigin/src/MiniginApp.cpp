#include "MiniginPCH.h"
#include "MiniginApp.h"

#include <chrono>
#include <thread>
#include <SDL.h>
#include "imgui.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"

#include "InputManager.h"

#include "SceneManager.h"
#include "ImGuiWrapper.h"
#include "Physics.h"
#include "SettingsManager.h"

void dae::MiniginApp::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	SettingsManager::GetInstance().LoadSettings("settings.ini");

	const WindowSettings windowSettings = SettingsManager::GetInstance().GetWindowSettings();

	m_Window = SDL_CreateWindow(
		windowSettings.title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowSettings.width,
		windowSettings.height,
		windowSettings.resizable
			? SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
			: SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	Physics::GetInstance().Init();
}

void dae::MiniginApp::Cleanup()
{
	Physics::GetInstance().Destroy();
	Renderer::GetInstance().Destroy();

	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::MiniginApp::Run()
{
	Initialize();

	EngineSettings engineSettings = SettingsManager::GetInstance().GetEngineSettings();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init(engineSettings.resourcesLocation);

	LoadGame();

	{
		auto t = std::chrono::high_resolution_clock::now();
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		sceneManager.Prepare();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			Time::GetInstance().Update(lastTime);

			if (engineSettings.debug)
				ImGuiWrapper::NewFrame();

			Physics::GetInstance().Update();
			sceneManager.PhysicsUpdate();

			input.Update();

			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					doContinue = false;
					break;
				}

				if (engineSettings.debug)
					ImGuiWrapper::HandleEvents(e);

				input.ProcessEvents(e);
			}

			sceneManager.Update();
			renderer.Render();

			t = lastTime + std::chrono::milliseconds(m_MsPerFrame);
			lastTime = currentTime;
			std::this_thread::sleep_until(t);
		}
	}

	Cleanup();
}

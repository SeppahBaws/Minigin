#include "MiniginPCH.h"
#include "MiniginApp.h"

#include <chrono>
#include <thread>
#include <SDL.h>
#include "imgui.h"

#include "Core/Renderer.h"
#include "Core/ResourceManager.h"
#include "Core/Time.h"

#include "Input/InputManager.h"

#include "Scene/SceneManager.h"
#include "Utils/ImGuiWrapper.h"

void dae::MiniginApp::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	// TODO: make the window arguments available to the user application.
	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

void dae::MiniginApp::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::MiniginApp::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto t = std::chrono::high_resolution_clock::now();
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			Time::GetInstance().Update(lastTime);

			ImGuiWrapper::NewFrame();

			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					doContinue = false;
					break;
				}

				input.ProcessInput(e);
				ImGuiWrapper::HandleEvents(e);
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

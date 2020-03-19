#include "MiniginPCH.h"
#include "Minigin.h"

#include <chrono>
#include <thread>
#include <SDL.h>

#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Time.h"

#include "TextComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "FPSComponent.h"

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
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

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Demo");

	// Background
	GameObject* go = new GameObject();
	go->AddComponent<TransformComponent>();
	TextureComponent* pTextureComp = new TextureComponent();
	pTextureComp->SetTexture("background.jpg");
	go->AddComponent(pTextureComp);
	scene.Add(go);

	// DAE logo
	go = new GameObject();
	go->GetTransform()->SetPosition(216, 180);
	auto texture = new TextureComponent();
	texture->SetTexture("logo.png");
	go->AddComponent(texture);
	scene.Add(go);

	// Text
	go = new GameObject();
	go->GetTransform()->SetPosition(80, 20);
	auto text = new TextComponent();
	text->SetFont("Lingua.otf");
	text->SetSize(36);
	text->SetText("Programming 4 Assignment");
	text->SetColor({ 1.0f, 1.0f, 1.0f });
	go->AddComponent(text);
	scene.Add(go);

	// FPS
	go = new GameObject();
	go->GetTransform()->SetPosition(0, 0);
	text = new TextComponent();
	text->SetText("60 FPS");
	text->SetSize(24);
	text->SetColor(Color(1.0f, 0.0f, 1.0f));
	go->AddComponent(text);
	go->AddComponent(new FPSComponent());
	scene.Add(go);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
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
			
			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();

			t = lastTime + std::chrono::milliseconds(m_MsPerFrame);
			lastTime = currentTime;
			std::this_thread::sleep_until(t);
		}
	}

	Cleanup();
}

#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"

using namespace std;
using namespace std::chrono;

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
	go->AddComponent(text);
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
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			
			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();
			
			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

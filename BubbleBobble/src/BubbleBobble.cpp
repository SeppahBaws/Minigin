#include "pch.h"
#include "BubbleBobble.h"

#include "ColliderComponent.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Components.h"
#include "EntityTags.h"
#include "GameObject.h"
#include "Game/GameManager.h"
#include "Game/LivesDisplay.h"
#include "Game/PlayerBehaviour.h"
#include "Game/ZenChanBehaviour.h"
#include "MainMenu/GameOverManager.h"
#include "MainMenu/MainMenuManager.h"
#include "MainMenu/PlayButton.h"
#include "MainMenu/QuitButton.h"
#include "Test/FPSComponent.h"

using namespace dae;

void BubbleBobble::LoadGame() const
{
	SetupInput();
	SetupScene();
}

void BubbleBobble::SetupInput() const
{
	// Game scene
	InputManager::GetInstance().SetupAxis("MovementHorizontal", {
		{
			{ Key::D, 1.0f },
			{ Key::A, -1.0f },
			{ GamepadAxis::LeftThumbX, 1.0f },
		}
	});

	InputManager::GetInstance().SetupAction("Jump", {
		{
			{ Key::Space, InputState::Pressed },
			{ GamepadButton::A, InputState::Pressed },
		}
	});

	InputManager::GetInstance().SetupAction("Shoot", {
		{
			{ Key::E, InputState::Pressed },
			{ GamepadButton::X, InputState::Pressed },
		}
	});

	// Main menu
	InputManager::GetInstance().SetupAction("MainMenu_SelectNext", {
		{
			{ Key::Down, InputState::Pressed },
			{ GamepadButton::DPadDown, InputState::Pressed }
		}
	});

	InputManager::GetInstance().SetupAction("MainMenu_SelectPrevious", {
		{
			{ Key::Up, InputState::Pressed },
			{ GamepadButton::DPadUp, InputState::Pressed }
		}
	});

	InputManager::GetInstance().SetupAction("MainMenu_Activate", {
		{
			{ Key::Enter, InputState::Pressed },
			{ GamepadButton::A, InputState::Pressed }
		}
	});
}

void BubbleBobble::SetupScene() const
{
#pragma region Game scene
	// Game Scene
	{
		Scene& scene = SceneManager::GetInstance().CreateScene("Game");

#pragma region objects
		// Background
		GameObject* go = new GameObject();
		go->GetTransform()->SetPosition({ 0.0f, 0.0f, 0.0f });
		TextureComponent* pTextureComp = new TextureComponent();
		pTextureComp->SetTexture("background.jpg");
		go->AddComponent(pTextureComp);
		scene.Add(go);

		// Game manager
		go = new GameObject();
		GameManager* gameManager = new GameManager();
		go->AddComponent(gameManager);
		scene.Add(go);

		// FPS
		go = new GameObject();
		go->GetTransform()->SetPosition({ 0, 0, 0 });
		go->AddComponent(new FPSComponent());
		scene.Add(go);

		// Lives display
		go = new GameObject();
		go->GetTransform()->SetPosition({ 100, 10, 0 });
		go->AddComponent(new TextComponent("lives: 4"));
		LivesDisplay* livesDisplay = new LivesDisplay();
		go->AddComponent(livesDisplay);
		scene.Add(go);

		// Player
		go = new GameObject();
		go->SetTag(EntityTags::ET_Player);
		go->GetTransform()->SetPosition({ 200, 200, 0 });
		go->AddComponent(new RigidBodyComponent(glm::vec2(48.0f, 48.0f), RigidBodyType::Dynamic));
		go->AddComponent(new ColliderComponent({ 0.0f, 0.0f }, { 48.0f, 48.0f }));
		PlayerBehaviour* pPlayerBehaviour = new PlayerBehaviour();
		pPlayerBehaviour->AddObserver(livesDisplay);
		pPlayerBehaviour->AddObserver(gameManager);
		go->AddComponent(pPlayerBehaviour);
		go->AddComponent(new SpriteComponent("sprites/bub_run.png", 1, 2, 3.0f, 3));
		scene.Add(go);

		// Zen-chan
		go = new GameObject();
		go->SetTag(EntityTags::ET_Enemy);
		go->GetTransform()->SetPosition({ 300, 200, 0 });
		go->AddComponent(new ZenChanBehaviour());
		go->AddComponent(new RigidBodyComponent(glm::vec2(48.0f, 48.0f), RigidBodyType::Dynamic));
		go->AddComponent(new ColliderComponent({ 0.0f, 0.0f }, { 48.0f, 48.0f }));
		go->AddComponent(new SpriteComponent("sprites/zen-chan_run.png", 1, 2, 3.0f, 3));
		scene.Add(go);
#pragma endregion

#pragma region world
		/* Edges of the world */

		// Bottom
		go = new GameObject();
		go->SetTag(EntityTags::ET_Ground);
		go->GetTransform()->SetPosition({ 0, 460, 0 });
		go->AddComponent(new RigidBodyComponent(glm::vec2(640.0f, 20.0f), RigidBodyType::Static));
		go->AddComponent(new ColliderComponent({ 0.0f, 0.0f }, { 640.0f, 20.0f }));
		go->AddComponent(new SpriteComponent("wall_tile.png", 1, 1, 3, 0));
		scene.Add(go);

		// Top
		go = new GameObject();
		go->SetTag(EntityTags::ET_Wall);
		go->GetTransform()->SetPosition({ 0, 0, 0 });
		go->AddComponent(new RigidBodyComponent(glm::vec2(640.0f, 20.0f), RigidBodyType::Static));
		go->AddComponent(new ColliderComponent({ 0.0f, 0.0f }, { 640.0f, 20.0f }));
		go->AddComponent(new SpriteComponent("wall_tile.png", 1, 1, 3, 0));
		scene.Add(go);

		// Left
		go = new GameObject();
		go->SetTag(EntityTags::ET_Wall);
		go->GetTransform()->SetPosition({ 0, 0, 0 });
		go->AddComponent(new RigidBodyComponent(glm::vec2(20.0f, 480.0f), RigidBodyType::Static));
		go->AddComponent(new ColliderComponent({ 0.0f, 0.0f }, { 20.0f, 480.0f }));
		go->AddComponent(new SpriteComponent("wall_tile.png", 1, 1, 3, 0));
		scene.Add(go);

		// Right
		go = new GameObject();
		go->SetTag(EntityTags::ET_Wall);
		go->GetTransform()->SetPosition({ 620, 0, 0 });
		go->AddComponent(new RigidBodyComponent(glm::vec2(20.0f, 640.0f), RigidBodyType::Static));
		go->AddComponent(new ColliderComponent({ 0.0f, 0.0f }, { 20.0f, 640.0f }));
		go->AddComponent(new SpriteComponent("wall_tile.png", 1, 1, 3, 0));
		scene.Add(go);


		/* Platforms */

		// Top row
		go = new GameObject();
		go->SetTag(EntityTags::ET_Ground);
		go->GetTransform()->SetPosition({ 20, 170, 0 });
		go->AddComponent(new RigidBodyComponent(glm::vec2(60.0f, 25.0f), RigidBodyType::Static));
		go->AddComponent(new ColliderComponent({ 0.0f, 0.0f }, { 60.0f, 25.0f }));
		go->AddComponent(new SpriteComponent("wall_tile.png", 1, 1, 3, 0));
		scene.Add(go);

		go = new GameObject();
		go->SetTag(EntityTags::ET_Ground);
		go->GetTransform()->SetPosition({ 160, 170, 0 });
		go->AddComponent(new RigidBodyComponent(glm::vec2(320.0f, 25.0f), RigidBodyType::Static));
		go->AddComponent(new ColliderComponent({ 0.0f, 0.0f }, { 320.0f, 25.0f }));
		go->AddComponent(new SpriteComponent("wall_tile.png", 1, 1, 3, 0));
		scene.Add(go);

		go = new GameObject();
		go->SetTag(EntityTags::ET_Ground);
		go->GetTransform()->SetPosition({ 560, 170, 0 });
		go->AddComponent(new RigidBodyComponent(glm::vec2(60.0f, 25.0f), RigidBodyType::Static));
		go->AddComponent(new ColliderComponent({ 0.0f, 0.0f }, { 60.0f, 25.0f }));
		go->AddComponent(new SpriteComponent("wall_tile.png", 1, 1, 3, 0));
		scene.Add(go);

		// Bottom row
		go = new GameObject();
		go->SetTag(EntityTags::ET_Ground);
		go->GetTransform()->SetPosition({ 20, 320, 0 });
		go->AddComponent(new RigidBodyComponent(glm::vec2(100.0f, 25.0f), RigidBodyType::Static));
		go->AddComponent(new ColliderComponent({ 0.0f, 0.0f }, { 100.0f, 25.0f }));
		go->AddComponent(new SpriteComponent("wall_tile.png", 1, 1, 3, 0));
		scene.Add(go);

		go = new GameObject();
		go->SetTag(EntityTags::ET_Ground);
		go->GetTransform()->SetPosition({ 200, 320, 0 });
		go->AddComponent(new RigidBodyComponent(glm::vec2(240.0f, 25.0f), RigidBodyType::Static));
		go->AddComponent(new ColliderComponent({ 0.0f, 0.0f }, { 240.0f, 25.0f }));
		go->AddComponent(new SpriteComponent("wall_tile.png", 1, 1, 3, 0));
		scene.Add(go);

		go = new GameObject();
		go->SetTag(EntityTags::ET_Ground);
		go->GetTransform()->SetPosition({ 520, 320, 0 });
		go->AddComponent(new RigidBodyComponent(glm::vec2(100.0f, 25.0f), RigidBodyType::Static));
		go->AddComponent(new ColliderComponent({ 0.0f, 0.0f }, { 100.0f, 25.0f }));
		go->AddComponent(new SpriteComponent("wall_tile.png", 1, 1, 3, 0));
		scene.Add(go);
#pragma endregion
	}
#pragma endregion

#pragma region Main Menu
	// Main menu
	{
		Scene& scene = SceneManager::GetInstance().CreateScene("MainMenu");

		// Main menu manager
		GameObject* go = new GameObject();
		MainMenuManager* mainMenuManager = new MainMenuManager();
		go->AddComponent(mainMenuManager);
		scene.Add(go);

		// Play button
		go = new GameObject();
		go->GetTransform()->SetPosition({ 290.0f, 300.0f, 0.0f });
		go->AddComponent(new TextComponent("Play", "Lingua.otf", 32));
		Button* pButton = new PlayButton();
		go->AddComponent(pButton);
		scene.Add(go);
		mainMenuManager->AddButton(pButton);

		// Quit button
		go = new GameObject();
		go->GetTransform()->SetPosition({ 290.0f, 350.0f, 0.0f });
		go->AddComponent(new TextComponent("Quit", "Lingua.otf", 32));
		pButton = new QuitButton();
		go->AddComponent(pButton);
		scene.Add(go);
		mainMenuManager->AddButton(pButton);

		// Xbox A prompt
		go = new GameObject();
		go->GetTransform()->SetPosition({ 240.0f, 300.0f, 0.0f });
		go->AddComponent(new SpriteComponent("sprites/xbox-a.png", 1, 2, 3, 4));
		scene.Add(go);
		mainMenuManager->RegisterSpritePrompt(go);

		// Logo
		go = new GameObject();
		go->GetTransform()->SetPosition({ 170.0f, 10.0f, 0.0f });
		TextureComponent* pTexture = new TextureComponent();
		pTexture->SetTexture("bubblebobble-logo.png");
		go->AddComponent(pTexture);
		scene.Add(go);

		// FPS
		go = new GameObject();
		go->GetTransform()->SetPosition({ 0, 0, 0 });
		go->AddComponent(new FPSComponent());
		scene.Add(go);

		SceneManager::GetInstance().ActivateScene("MainMenu");
	}
#pragma endregion

#pragma region Game Over
	// Game Over
	{
		Scene& scene = SceneManager::GetInstance().CreateScene("GameOver");

		// Game Over manager
		GameObject* go = new GameObject();
		go->AddComponent(new GameOverManager());
		scene.Add(go);
		
		// Logo
		go = new GameObject();
		go->GetTransform()->SetPosition({ 170.0f, 10.0f, 0.0f });
		TextureComponent* pTexture = new TextureComponent();
		pTexture->SetTexture("bubblebobble-logo.png");
		go->AddComponent(pTexture);
		scene.Add(go);

		// Game over text
		go = new GameObject();
		go->GetTransform()->SetPosition({ 250.0f, 300.0f, 0.0f });
		go->AddComponent(new TextComponent("Game Over!", "Lingua.otf", 32));
		scene.Add(go);

		// Continue text
		go = new GameObject();
		go->GetTransform()->SetPosition({ 250.0f, 390.0f, 0.0f });
		go->AddComponent(new TextComponent("To main menu", "Lingua.otf", 24, Color(1.0f, 0.0f, 0.0f)));
		scene.Add(go);

		// Xbox A prompt
		go = new GameObject();
		go->GetTransform()->SetPosition({ 314, 420.0f, 0.0f });
		go->AddComponent(new SpriteComponent("sprites/xbox-a.png", 1, 2, 3, 4));
		scene.Add(go);
	}
#pragma endregion
}

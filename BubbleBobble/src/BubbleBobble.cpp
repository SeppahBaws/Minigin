#include "pch.h"
#include "BubbleBobble.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Components.h"
#include "GameObject.h"

#include "Components/FPSComponent.h"
#include "Components/PlayerBehaviour.h"

using namespace dae;

void BubbleBobble::LoadGame() const
{
	SetupInput();
	SetupScene();
}

void BubbleBobble::SetupInput() const
{
	InputManager::GetInstance().SetupAxis("MovementHorizontal", {
		{
			{ GamepadAxis::LeftThumbX, 1.0f },
			{ Key::D, 1.0f },
			{ Key::A, -1.0f },
		}
	});
	
	InputManager::GetInstance().SetupAxis("MovementVertical", {
		{
			{ GamepadAxis::LeftThumbY, 1.0f },
			{ Key::W, -1.0f },
			{ Key::S, 1.0f },
		}
	});
	
	InputManager::GetInstance().SetupAction("Shoot", {
		{
			{ GamepadButton::A, InputState::Pressed },
			{ Key::Space, InputState::Pressed },
			{ MouseButton::Left, InputState::Pressed }
		}
	});
}

void BubbleBobble::SetupScene() const
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

	// Player
	go = new GameObject();
	go->GetTransform()->SetPosition(200, 200);
	go->AddComponent<PlayerBehaviour>();
	go->AddComponent(new SpriteComponent("PlayerSprites/bub_run.png", 1, 8, 3.0f));
	// go->AddComponent(new SpriteComponent("test-player-run.png", 1, 8, 7.0f));
	scene.Add(go);
}

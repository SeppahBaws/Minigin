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
			{ Key::D, 1.0f },
			{ Key::A, -1.0f },
			{ GamepadAxis::LeftThumbX, 1.0f },
		}
	});

	InputManager::GetInstance().SetupAxis("MovementVertical", {
		{
			{ Key::W, -1.0f },
			{ Key::S, 1.0f },
			{ GamepadAxis::LeftThumbY, -1.0f },
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
			{ GamepadButton::B, InputState::Pressed },
		}
	});
}

void BubbleBobble::SetupScene() const
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Demo");

	// Background
	GameObject* go = new GameObject();
	go->GetTransform()->SetPosition({ 0.0f, 0.0f, 0.0f });
	TextureComponent* pTextureComp = new TextureComponent();
	pTextureComp->SetTexture("background.jpg");
	go->AddComponent(pTextureComp);
	scene.Add(go);

	// DAE logo
	go = new GameObject();
	go->GetTransform()->SetPosition({ 216, 180, 0 });
	TextureComponent* texture = new TextureComponent();
	texture->SetTexture("logo.png");
	go->AddComponent(texture);
	scene.Add(go);

	// FPS
	go = new GameObject();
	go->GetTransform()->SetPosition({ 0, 0, 0 });
	go->AddComponent(new FPSComponent());
	scene.Add(go);

	// Player
	go = new GameObject();
	go->GetTransform()->SetPosition({ 200, 200, 0 });
	go->AddComponent(new RigidBodyComponent(glm::vec2(48.0f, 48.0f), RigidBodyType::Dynamic));
	go->AddComponent<PlayerBehaviour>();
	go->AddComponent(new SpriteComponent("PlayerSprites/bub_run.png", 1, 8, 3.0f));
	scene.Add(go);

	// Ground
	go = new GameObject();
	go->GetTransform()->SetPosition({ 150, 400, 0 });
	go->AddComponent(new RigidBodyComponent(glm::vec2(130.0f, 25.0f), RigidBodyType::Static));
	TextureComponent* pGroundTexture = new TextureComponent();
	pGroundTexture->SetTexture("PlayerSprites/bub_run.png");
	go->AddComponent(pGroundTexture);
	scene.Add(go);
}

#include "pch.h"
#include "BubbleBobble.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Components.h"
#include "GameObject.h"

#include "Components/PlayerBehaviour.h"
#include "Test/FPSComponent.h"
#include "Test/SceneSwitcher.h"

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

#pragma region objects
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
	go->AddComponent(new PlayerBehaviour());
	go->AddComponent(new SpriteComponent("sprites/bub_run.png", 1, 2, 3.0f, 3));
	scene.Add(go);

	// Zen-chan
	go = new GameObject();
	go->GetTransform()->SetPosition({ 300, 200, 0 });
	go->AddComponent(new RigidBodyComponent(glm::vec2(48.0f, 48.0f), RigidBodyType::Dynamic));
	go->AddComponent(new SpriteComponent("sprites/zen-chan_run.png", 1, 2, 3.0f, 3));
	scene.Add(go);

	// Maita
	go = new GameObject();
	go->GetTransform()->SetPosition({ 300, 100, 0 });
	go->AddComponent(new RigidBodyComponent(glm::vec2(48.0f, 48.0f), RigidBodyType::Dynamic));
	go->AddComponent(new SpriteComponent("sprites/maita_run.png", 1, 2, 3.0f, 3));
	scene.Add(go);

	// Fries
	go = new GameObject();
	go->GetTransform()->SetPosition({ 50, 200, 0 });
	go->AddComponent(new RigidBodyComponent(glm::vec2(48.0f, 48.0f), RigidBodyType::Dynamic));
	go->AddComponent(new SpriteComponent("sprites/fries.png", 1, 1, 3.0f, 3));
	scene.Add(go);

	// Watermelon
	go = new GameObject();
	go->GetTransform()->SetPosition({ 100, 200, 0 });
	go->AddComponent(new RigidBodyComponent(glm::vec2(48.0f, 48.0f), RigidBodyType::Dynamic));
	go->AddComponent(new SpriteComponent("sprites/watermelon.png", 1, 1, 3.0f, 3));
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new SceneSwitcher());
	scene.Add(go);
#pragma endregion


#pragma region world
	/* Edges of the world */

	// Bottom
	go = new GameObject();
	go->GetTransform()->SetPosition({ 0, 460, 0 });
	go->AddComponent(new RigidBodyComponent(glm::vec2(640.0f, 20.0f), RigidBodyType::Static));
	scene.Add(go);

	// Top
	go = new GameObject();
	go->GetTransform()->SetPosition({ 0, 0, 0 });
	go->AddComponent(new RigidBodyComponent(glm::vec2(640.0f, 20.0f), RigidBodyType::Static));
	scene.Add(go);

	// Left
	go = new GameObject();
	go->GetTransform()->SetPosition({ 0, 0, 0 });
	go->AddComponent(new RigidBodyComponent(glm::vec2(20.0f, 480.0f), RigidBodyType::Static));
	scene.Add(go);

	// Right
	go = new GameObject();
	go->GetTransform()->SetPosition({ 620, 0, 0 });
	go->AddComponent(new RigidBodyComponent(glm::vec2(20.0f, 640.0f), RigidBodyType::Static));
	scene.Add(go);


	/* Platforms */
	
#pragma endregion

	Scene& scene2 = SceneManager::GetInstance().CreateScene("Demo 2");

	go = new GameObject();
	go->GetTransform()->SetPosition({ 0, 200, 0 });
	texture = new TextureComponent();
	texture->SetTexture("logo.png");
	go->AddComponent(texture);
	scene2.Add(go);

	go = new GameObject();
	go->AddComponent(new SceneSwitcher());
	scene2.Add(go);
}

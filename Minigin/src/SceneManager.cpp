#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Prepare()
{
	for (auto& scene : m_Scenes)
	{
		scene->Prepare();
	}
}


void dae::SceneManager::PhysicsUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->PhysicsUpdate();
	}
}

void dae::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::RenderImGui()
{
	for (const auto& scene : m_Scenes)
	{
		scene->RenderImGui();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

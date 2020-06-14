#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

namespace dae
{
	void SceneManager::Prepare()
	{
		for (Scene* scene : m_Scenes)
		{
			scene->Prepare();
		}
	}

	void SceneManager::PhysicsUpdate()
	{
		m_pActiveScene->PhysicsUpdate();
	}

	void SceneManager::Update()
	{
		m_pActiveScene->Update();
	}

	void SceneManager::Render()
	{
		m_pActiveScene->Render();
	}

	void SceneManager::RenderImGui()
	{
		m_pActiveScene->RenderImGui();
	}

	SceneManager::~SceneManager()
	{
		for (Scene* scene : m_Scenes)
		{
			delete scene;
			scene = nullptr;
		}
		m_Scenes.clear();

		m_pActiveScene = nullptr;
	}

	Scene& SceneManager::CreateScene(const std::string& name)
	{
		Scene* scene = new Scene(name);
		m_Scenes.push_back(scene);

		if (m_pActiveScene == nullptr)
			m_pActiveScene = scene;

		return *scene;
	}

	void SceneManager::ActivateScene(const std::string& name)
	{
		for (Scene* scene : m_Scenes)
		{
			if (scene->GetName() == name)
			{
				m_pActiveScene = scene;
				return;
			}
		}

		std::cerr << "ERROR: No scene with name " << name << " was found!" << std::endl;
	}
}

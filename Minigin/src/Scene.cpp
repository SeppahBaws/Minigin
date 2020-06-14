#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

#include "Physics.h"

namespace dae
{
	Scene::Scene(const std::string& name)
		: m_Name(name)
	{
		m_pPhysicsWorld = Physics::GetInstance().CreateWorld();
		m_pPhysicsWorld->SetContactListener(&m_ContactListener);
	}

	Scene::~Scene()
	{
		for (GameObject* pObject : m_Objects)
		{
			delete pObject;
			pObject = nullptr;
		}
		m_Objects.clear();

		CleanupRemovedObjects();

		delete m_pPhysicsWorld;
	}

	void Scene::Add(GameObject* object)
	{
		object->SetScene(this);
		m_Objects.push_back(object);

		if (m_IsInGameLoop)
		{
			object->Prepare();
		}
	}

	void Scene::Remove(GameObject* object)
	{
		m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
		m_RemovedObjects.push_back(object);
	}

	void Scene::Prepare()
	{
		for (GameObject* object : m_Objects)
		{
			object->Prepare();
		}
	}

	void Scene::PhysicsUpdate()
	{
		Physics::GetInstance().Update(m_pPhysicsWorld);

		for (GameObject* object : m_Objects)
		{
			object->PhysicsUpdate();
		}
	}

	void Scene::Update()
	{
		m_IsInGameLoop = true;

		CleanupRemovedObjects(); // Cleanup any removed objects from previous frame

		for (size_t i = 0; i < m_Objects.size(); i++)
		{
			m_Objects[i]->Update();
		}
	}

	void Scene::Render() const
	{
		for (const GameObject* object : m_Objects)
		{
			object->Render();
		}
	}

	void Scene::RenderImGui() const
	{
		for (const GameObject* object : m_Objects)
		{
			object->RenderImGui();
		}
	}

	void Scene::Cleanup()
	{
		m_IsInGameLoop = false;
		m_ContactListener.SetCleanup(true);
	}

	void Scene::CleanupRemovedObjects()
	{
		for (GameObject* pObject : m_RemovedObjects)
		{
			delete pObject;
			pObject = nullptr;
		}
		m_RemovedObjects.clear();
	}
}

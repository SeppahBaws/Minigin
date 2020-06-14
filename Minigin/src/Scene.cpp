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

		delete m_pPhysicsWorld;
	}

	void Scene::Add(GameObject* object)
	{
		object->SetScene(this);
		m_Objects.push_back(object);
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
		for (GameObject* object : m_Objects)
		{
			object->Update();
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
}

#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

namespace dae
{
	unsigned int Scene::m_IdCounter = 0;

	Scene::Scene(const std::string& name)
		: m_Name(name)
	{
	}

	Scene::~Scene()
	{
		for (GameObject* pObject : m_Objects)
		{
			delete pObject;
			pObject = nullptr;
		}
	}

	void Scene::Add(GameObject* object)
	{
		m_Objects.push_back(object);
	}

	void Scene::Prepare()
	{
		for (GameObject* object : m_Objects)
		{
			object->Prepare();
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

#include "MiniginPCH.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "Scene.h"

namespace dae
{
	GameObject::GameObject()
	{
		m_pTransform = new TransformComponent();
		AddComponent(m_pTransform);
	}

	GameObject::~GameObject()
	{
		for (BaseComponent* pComp : m_pComponents)
		{
			SafeDelete(pComp);
		}
		m_pComponents.clear();
	}

	void GameObject::AddComponent(BaseComponent* pComp)
	{
		pComp->m_pGameObject = this;
		m_pComponents.push_back(pComp);
	}

	void GameObject::Prepare()
	{
		for (const auto component : m_pComponents)
		{
			component->OnPrepare();
		}
	}

	void GameObject::PhysicsUpdate()
	{
		for (const auto component : m_pComponents)
		{
			component->OnPhysicsUpdate();
		}
	}

	void GameObject::Update()
	{
		for (size_t i = 0; i < m_pComponents.size(); i++)
		{
			m_pComponents[i]->OnUpdate();
		}
		// for (const auto component : m_pComponents)
		// {
		// 	component->OnUpdate();
		// }
	}

	void GameObject::Render() const
	{
		for (const auto component : m_pComponents)
		{
			component->OnRender();
		}
	}

	void GameObject::RenderImGui() const
	{
		for (const auto component : m_pComponents)
		{
			component->OnImGui();
		}
	}

	void GameObject::OnCollisionBegin(GameObject* pOther)
	{
		for (size_t i = 0; i < m_pComponents.size(); i++)
		{
			m_pComponents[i]->OnCollisionBegin(pOther);
		}
		// for (const auto component : m_pComponents)
		// {
		// 	component->OnCollisionBegin(pOther);
		// }
	}

	void GameObject::OnCollisionEnd(GameObject* pOther)
	{
		for (size_t i = 0; i < m_pComponents.size(); i++)
		{
			m_pComponents[i]->OnCollisionEnd(pOther);
		}
		// for (const auto component : m_pComponents)
		// {
		// 	component->OnCollisionEnd(pOther);
		// }
	}

	TransformComponent* GameObject::GetTransform() const
	{
		return m_pTransform;
	}

	void GameObject::SetScene(Scene* pScene)
	{
		m_pScene = pScene;
	}

	Scene* GameObject::GetScene() const
	{
		return m_pScene;
	}

	void GameObject::SetTag(int tag)
	{
		m_Tag = tag;
	}

	int GameObject::GetTag() const
	{
		return m_Tag;
	}
}

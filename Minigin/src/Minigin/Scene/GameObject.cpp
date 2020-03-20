#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"

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

	void GameObject::Update()
	{
		for (const auto component : m_pComponents)
		{
			component->OnUpdate();
		}
	}

	void GameObject::Render() const
	{
		for (const auto component : m_pComponents)
		{
			component->OnRender();
		}
	}

	TransformComponent* GameObject::GetTransform() const
	{
		return m_pTransform;
	}
}

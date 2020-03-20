#pragma once
#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;

		TransformComponent* GetTransform() const;

	public:
		/*
		 * Adds a new component of the given type.
		 */
		template<typename T>
		void AddComponent()
		{
			T* pComp = new T();
			pComp->m_pGameObject = this;
			m_pComponents.push_back(pComp);
		}

		/*
		 * Adds an already existing component.
		 */
		void AddComponent(BaseComponent* pComp);

		/*
		 * Returns the component of requested type.
		 * If no component was found, it returns nullptr.
		 */
		template<typename T>
		T* GetComponent()
		{
			for (const BaseComponent* pComp : m_pComponents)
			{
				if (pComp && typeid(*pComp) == typeid(T))
					return (T*)pComp;
			}

			return nullptr;
		}

	private:
		TransformComponent* m_pTransform;
		std::vector<BaseComponent*> m_pComponents;
	};
}

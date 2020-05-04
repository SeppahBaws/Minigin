#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"

#include <type_traits>

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

		void Prepare();
		void Update();
		void Render() const;
		void RenderImGui() const;

		TransformComponent* GetTransform() const;

	public:
		/*
		 * Adds a new component of the given type.
		 */
		template<typename T>
		typename std::enable_if<std::is_base_of<BaseComponent, T>::value, void>::type
		AddComponent()
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
		typename std::enable_if<std::is_base_of<BaseComponent, T>::value, T*>::type
		GetComponent()
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

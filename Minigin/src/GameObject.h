#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"

#include <type_traits>

namespace dae
{
	class Texture2D;
	class Scene;

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
		void PhysicsUpdate();
		void Update();
		void Render() const;
		void RenderImGui() const;

		void OnCollisionBegin(GameObject* pOther);
		void OnCollisionEnd(GameObject* pOther);

		TransformComponent* GetTransform() const;

		void SetScene(Scene* pScene);
		Scene* GetScene() const;

		void SetTag(int tag);
		int GetTag() const;

	public:
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

		/*
		 * Returns a vector of all components of requested type.
		 * If no component was found, this will return an empty vector.
		 */
		template<typename T>
		typename std::enable_if<std::is_base_of<BaseComponent, T>::value, std::vector<T*>>::type
		GetComponents()
		{
			std::vector<T*> components;
			for (const BaseComponent* pComp : m_pComponents)
			{
				if (pComp && typeid(*pComp) == typeid(T))
					components.push_back((T*)pComp);
			}
			return components;
		}

	private:
		TransformComponent* m_pTransform;
		std::vector<BaseComponent*> m_pComponents;
		int m_Tag = 0;
		Scene* m_pScene;
	};
}

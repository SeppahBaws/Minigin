#pragma once
#include <string>
#include <vector>

#include "ContactListener.h"
#include "SceneManager.h"

class b2World;

namespace dae
{
	class GameObject;
	class SceneManager;
	class Scene
	{
	public:
		void Add(GameObject* object);
		void Remove(GameObject* object);

		void Prepare();

		void PhysicsUpdate();
		void Update();
		void Render() const;
		void RenderImGui() const;

		void Cleanup();

		const std::string& GetName() const { return m_Name; }
		b2World* GetPhysicsWorld() const { return m_pPhysicsWorld; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		void CleanupRemovedObjects();

	private: 
		friend Scene& SceneManager::CreateScene(const std::string& name);
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector<GameObject*> m_Objects{};
		std::vector<GameObject*> m_RemovedObjects{};

		b2World* m_pPhysicsWorld;
		ContactListener m_ContactListener;

		bool m_IsInGameLoop = false;
	};
}

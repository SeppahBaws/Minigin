#pragma once
#include <string>
#include <vector>

#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class SceneManager;
	class Scene
	{
	public:
		void Add(GameObject* object);

		void Prepare();
		void PhysicsUpdate();
		void Update();
		void Render() const;
		void RenderImGui() const;

		const std::string& GetName() const { return m_Name; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		friend Scene& SceneManager::CreateScene(const std::string& name);
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector<GameObject*> m_Objects{};

		static unsigned int m_IdCounter;
	};
}

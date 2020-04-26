#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
	public:
		void Add(GameObject* object);

		void Update();
		void Render() const;
		void RenderImGui() const;

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

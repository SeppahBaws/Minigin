#pragma once
#include "Singleton.h"

#include <vector>
#include <string>
#include <memory>

namespace dae
{
	class CameraComponent;
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void ActivateScene(const std::string& name);

		void Prepare();
		void PhysicsUpdate();
		void Update();
		void Render();
		void RenderImGui();
		void Cleanup();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		~SceneManager();
		std::vector<Scene*> m_Scenes;
		Scene* m_pActiveScene = nullptr;
	};
}

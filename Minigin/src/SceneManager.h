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

		void Prepare();
		void PhysicsUpdate();
		void Update();
		void Render();
		void RenderImGui();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}

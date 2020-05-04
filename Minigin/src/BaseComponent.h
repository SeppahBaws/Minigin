#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent()
		{
			m_pGameObject = nullptr;
		}
		virtual ~BaseComponent()
		{
			m_pGameObject = nullptr;
		}

		virtual void OnPrepare() {}

		virtual void OnUpdate() {}
		virtual void OnRender() {}
		virtual void OnImGui() {}

		GameObject* GetGameObject() const { return m_pGameObject; }

	protected:
		friend class GameObject;
		GameObject* m_pGameObject;
	};
}

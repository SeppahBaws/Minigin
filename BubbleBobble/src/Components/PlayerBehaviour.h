#pragma once

#include "BaseComponent.h"

namespace dae
{
	class PlayerBehaviour final : public BaseComponent
	{
	public:
		PlayerBehaviour();
		virtual ~PlayerBehaviour() = default;
		PlayerBehaviour(const PlayerBehaviour& other) = delete;
		PlayerBehaviour(PlayerBehaviour&& other) noexcept = delete;
		PlayerBehaviour& operator=(const PlayerBehaviour& other) = delete;
		PlayerBehaviour& operator=(PlayerBehaviour&& other) noexcept = delete;

		void OnUpdate() override;
		void OnImGui() override;

		void OnCollisionBegin(GameObject* pObject) override;
		void OnCollisionEnd(GameObject* pObject) override;

	private:
		float m_MovementSpeed;
		float m_MovementForce;
		float m_JumpForce;

		bool m_IsOnGround;
	};
}

#pragma once

#include <Minigin.h>

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

	private:
		float m_MovementSpeed;
	};
}

#pragma once
#include "BaseComponent.h"

class b2Body;

#pragma warning(push)
#pragma warning(disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

namespace dae
{
	enum class RigidBodyType
	{
		Dynamic,
		Static,
		Kinematic,
	};

	class RigidBodyComponent final : public BaseComponent
	{
	public:
		RigidBodyComponent(const glm::vec2& size, RigidBodyType type = RigidBodyType::Static);

		void ApplyForce(const glm::vec2& force);
		void ApplyImpulse(const glm::vec2& impulse);

		void UpdateBodyTransform(const glm::vec2& position, float rotation);

		void OnPrepare() override;
		void OnPhysicsUpdate() override;
		void OnImGui() override;

	private:
		glm::vec2 m_Size;
		RigidBodyType m_Type;
		b2Body* m_pBody;
	};
}

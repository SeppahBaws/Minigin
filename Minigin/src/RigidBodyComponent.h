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
		~RigidBodyComponent();

		void ApplyForce(const glm::vec2& force);
		void ApplyImpulse(const glm::vec2& impulse);
		glm::vec2 GetLinearVelocity() const;
		void SetLinearVelocity(const glm::vec2& velocity);

		void OnPrepare() override;
		void OnPhysicsUpdate() override;
		void OnImGui() override;

	private:
		glm::vec2 m_Size;
		RigidBodyType m_Type;
		b2Body* m_pBody;
	};
}

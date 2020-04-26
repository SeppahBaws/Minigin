#pragma once
#include "BaseComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent() = default;
		virtual ~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z = 0.0f);

	private:
		glm::vec3 m_Position;
	};
}

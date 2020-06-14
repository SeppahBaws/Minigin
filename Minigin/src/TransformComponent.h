#pragma once
#include "BaseComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
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
		void SetPosition(const glm::vec3& pos);
		void Translate(const glm::vec2& movement);
		void Translate(const glm::vec3& movement);

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation);

	private:
		glm::vec3 m_Position;
		float m_Rotation;
	};
}

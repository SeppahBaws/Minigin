#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

#include "BaseComponent.h"

struct b2FixtureDef;

namespace dae
{
	class ColliderComponent final : public BaseComponent
	{
	public:
		ColliderComponent(const glm::vec2& offset, const glm::vec2& size, bool isTrigger = false);

		glm::vec2 GetOffset() const { return m_Offset; }
		glm::vec2 GetSize() const { return m_Size; }
		bool GetIsTrigger() const { return m_IsTrigger; }

	private:
		glm::vec2 m_Offset;
		glm::vec2 m_Size;
		bool m_IsTrigger;
	};
}

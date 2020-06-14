#include "MiniginPCH.h"
#include "ColliderComponent.h"

namespace dae
{
	ColliderComponent::ColliderComponent(const glm::vec2& offset, const glm::vec2& size, bool isTrigger)
		: m_Offset(offset)
		, m_Size(size)
		, m_IsTrigger(isTrigger)
	{
	}
}

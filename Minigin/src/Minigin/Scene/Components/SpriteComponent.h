#pragma once
#include "BaseComponent.h"

#include "Minigin/Core/Texture2D.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)


namespace dae
{
	class SpriteComponent : public BaseComponent
	{
	public:
		SpriteComponent(const std::string& texture, int rows, int columns, float scale = 3.0f);
		virtual ~SpriteComponent();

		void OnUpdate() override;
		void OnRender() override;

	private:
		Texture2D* m_pTexture;
		int m_Rows, m_Columns;

		float m_Scale;

		const int m_FramesPerSec = 6;
		float m_AccumulatedTime;
		int m_CurrentFrame = 0;

		glm::vec2 m_FramePos;
		glm::vec2 m_FrameSize;
	};
}

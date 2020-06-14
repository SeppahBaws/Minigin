#pragma once
#include "BaseComponent.h"

#include "Texture2D.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)


namespace dae
{
	class SpriteComponent : public BaseComponent
	{
	public:
		SpriteComponent(const std::string& texture, int rows, int columns, float scale = 3.0f, int framesPerSec = 6);
		virtual ~SpriteComponent();

		void OnUpdate() override;
		void OnRender() override;

		void UpdateSprite(const std::string& texture, int rows, int columns, float scale = 3.0f, int framesPerSec = 6);

	private:
		void InitSprite(const std::string& texture, int rows, int columns);

	private:
		Texture2D* m_pTexture;
		int m_Rows, m_Columns;
		float m_Scale;

		int m_FramesPerSec;
		float m_AccumulatedTime = 0.0f;
		int m_CurrentFrame = 0;

		glm::vec2 m_FramePos;
		glm::vec2 m_FrameSize;
	};
}

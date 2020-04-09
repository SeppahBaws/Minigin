#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Minigin/Scene/GameObject.h"

#include "Minigin/Core/Renderer.h"
#include "Minigin/Core/ResourceManager.h"
#include "Minigin/Core/Time.h"

#include <SDL.h>

namespace dae
{
	SpriteComponent::SpriteComponent(const std::string& texture, int rows, int columns, float scale)
		: m_Rows(rows)
		, m_Columns(columns)
		, m_Scale(scale)
	{
		m_pTexture = ResourceManager::GetInstance().LoadTexture(texture);

		int frameWidth, frameHeight;
		m_pTexture->GetSize(frameWidth, frameHeight);

		m_FrameSize = glm::vec2(frameWidth / columns, frameHeight / rows);
	}

	SpriteComponent::~SpriteComponent()
	{
		delete m_pTexture;
	}

	void SpriteComponent::OnUpdate()
	{
		m_AccumulatedTime += Time::GetInstance().GetDeltaTime();

		if (m_AccumulatedTime >= 1.0f / float(m_FramesPerSec))
		{
			m_CurrentFrame++;
			if (m_CurrentFrame > m_Rows * m_Columns - 1)
				m_CurrentFrame = 0;

			m_AccumulatedTime -= 1.0f / float(m_FramesPerSec);
		}
	}

	void SpriteComponent::OnRender()
	{
		glm::vec3 pos = m_pGameObject->GetTransform()->GetPosition();

		const SDL_Rect srcRect = {
			int(m_FrameSize.x * (m_CurrentFrame % m_Columns)),
			int(m_FrameSize.y * (m_CurrentFrame / m_Columns)),
			int(m_FrameSize.x),
			int(m_FrameSize.y)
		};
		const SDL_Rect dstRect = {
			int(pos.x),
			int(pos.y),
			int(m_FrameSize.x * m_Scale),
			int(m_FrameSize.y * m_Scale)
		};

		Renderer::GetInstance().RenderTexture(*m_pTexture, srcRect, dstRect);
	}
}

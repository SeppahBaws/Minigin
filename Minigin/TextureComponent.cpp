#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

namespace dae
{
	TextureComponent::TextureComponent()
		: m_pTexture(nullptr)
	{
	}

	TextureComponent::~TextureComponent()
	{
		SafeDelete(m_pTexture);
	}

	void TextureComponent::SetTexture(const std::string& filename)
	{
		m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
	}

	void TextureComponent::OnRender()
	{
		const glm::vec3 pos = GetGameObject()->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

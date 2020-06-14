#include "pch.h"
#include "StretchedTextureRenderer.h"

#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"

StretchedTextureRenderer::StretchedTextureRenderer(const std::string& texture)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(texture);
}

StretchedTextureRenderer::~StretchedTextureRenderer()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void StretchedTextureRenderer::OnPrepare()
{
	m_pRB = m_pGameObject->GetComponent<dae::RigidBodyComponent>();
	if (!m_pRB)
		std::cout << "ERROR: Failed to find a RigidBodyComponent on this object!" << std::endl;
}

void StretchedTextureRenderer::OnRender()
{
	const glm::vec3 pos = m_pGameObject->GetTransform()->GetPosition();
	const glm::vec2 size = m_pRB->GetSize();

	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, size.x, size.y);
}

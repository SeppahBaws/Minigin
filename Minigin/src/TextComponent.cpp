#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

#include <SDL.h>
#include <SDL_ttf.h>

namespace dae
{
	TextComponent::TextComponent(const std::string& text, const std::string& font, unsigned int fontSize, Color color)
		: m_NeedsUpdate(true), m_Text(text), m_FontFile(font), m_FontSize(fontSize), m_Color(color), m_pTexture(nullptr)
	{
		m_pFont = ResourceManager::GetInstance().LoadFont(m_FontFile, m_FontSize);
	}

	TextComponent::~TextComponent()
	{
		SafeDelete(m_pFont);
		SafeDelete(m_pTexture);
	}

	void TextComponent::OnUpdate()
	{
		if (m_NeedsUpdate)
		{
			const auto surface = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color.GetSDL());
			if (surface == nullptr)
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}
			auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface);
			if (texture == nullptr)
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}
			SDL_FreeSurface(surface);
			SafeDelete(m_pTexture);
			m_pTexture = new Texture2D(texture);
			m_NeedsUpdate = false;
		}
	}

	void TextComponent::OnRender()
	{
		if (m_pTexture != nullptr)
		{
			const auto pos = m_pGameObject->GetTransform()->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		}
	}

	void TextComponent::SetText(const std::string& text)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}

	void TextComponent::SetFont(const std::string& font)
	{
		m_FontFile = font;
		ReloadFont();
	}

	void TextComponent::SetSize(unsigned int size)
	{
		m_FontSize = size;
		ReloadFont();
	}

	void TextComponent::SetColor(const Color& color)
	{
		m_Color = color;
		m_NeedsUpdate = true;
	}

	void TextComponent::ReloadFont()
	{
		SafeDelete(m_pFont);
		m_pFont = ResourceManager::GetInstance().LoadFont(m_FontFile, m_FontSize);

		m_NeedsUpdate = true;
	}
}

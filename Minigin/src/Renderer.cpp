#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "ImGuiWrapper.h"
#include "Texture2D.h"

#include <SDL.h>

namespace dae
{
	void Renderer::Init(SDL_Window* window)
	{
		m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (m_Renderer == nullptr)
		{
			throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
		}

		ImGuiWrapper::Init(window);
	}

	void Renderer::Render() const
	{
		SDL_RenderClear(m_Renderer);

		SceneManager::GetInstance().Render();

		SceneManager::GetInstance().RenderImGui();
		ImGuiWrapper::Render();

		SDL_RenderPresent(m_Renderer);
	}

	void Renderer::Destroy()
	{
		ImGuiWrapper::Destroy();

		if (m_Renderer != nullptr)
		{
			SDL_DestroyRenderer(m_Renderer);
			m_Renderer = nullptr;
		}
	}

	void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
	{
		SDL_Rect dst;
		dst.x = static_cast<int>(x);
		dst.y = static_cast<int>(y);
		SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
	}

	void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
	{
		SDL_Rect dst;
		dst.x = static_cast<int>(x);
		dst.y = static_cast<int>(y);
		dst.w = static_cast<int>(width);
		dst.h = static_cast<int>(height);
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
	}

	void Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& src, const SDL_Rect& dst) const
	{
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
	}

	void Renderer::DebugRenderPoint(const glm::vec2& point, const Color& color) const
	{
		const SDL_Color c = color.GetSDL();
		SDL_SetRenderDrawColor(m_Renderer, c.r, c.g, c.b, c.a);

		SDL_RenderDrawPoint(m_Renderer, static_cast<int>(point.x), static_cast<int>(point.y));
	}

	void Renderer::DebugRenderLine(const glm::vec2& p1, const glm::vec2& p2, const Color& color) const
	{
		const SDL_Color c = color.GetSDL();
		SDL_SetRenderDrawColor(m_Renderer, c.r, c.g, c.b, c.a);

		SDL_RenderDrawLine(m_Renderer,
			static_cast<int>(p1.x),
			static_cast<int>(p1.y),
			static_cast<int>(p2.x),
			static_cast<int>(p2.y));
	}

	void Renderer::DebugRenderRect(const glm::vec2& topLeft, const glm::vec2& bottomRight, const Color& color) const
	{
		const SDL_Color c = color.GetSDL();
		SDL_SetRenderDrawColor(m_Renderer, c.r, c.g, c.b, c.a);

		SDL_Rect rect = {
			static_cast<int>(topLeft.x),
			static_cast<int>(topLeft.y),
			static_cast<int>(bottomRight.x - topLeft.x),
			static_cast<int>(bottomRight.y - topLeft.y)
		};

		SDL_RenderDrawRect(m_Renderer, &rect);
	}
}

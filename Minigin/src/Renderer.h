#pragma once
#include "Singleton.h"
#include "Color.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;

namespace dae
{
	class Texture2D;

	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& src, const SDL_Rect& dst) const;

		void DebugRenderPoint(const glm::vec2& point, const Color& color = Color(1.0f, 0.0f, 0.0f, 1.0f)) const;
		void DebugRenderLine(const glm::vec2& p1, const glm::vec2& p2, const Color& color = Color(1.0f, 0.0f, 0.0f, 1.0f)) const;
		void DebugRenderRect(const glm::vec2& topLeft, const glm::vec2& bottomRight, const Color& color = Color(1.0f, 0.0f, 0.0f, 1.0f)) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};
	};
}


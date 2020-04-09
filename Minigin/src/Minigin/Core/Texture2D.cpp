#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

void dae::Texture2D::GetSize(int& width, int& height) const
{
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &width, &height);
}

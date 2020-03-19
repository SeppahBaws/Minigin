#include "MiniginPCH.h"
#include "Color.h"

namespace dae
{
	Color::Color(const glm::vec3& color)
	{
		this->r = ToWhole(color.r);
		this->g = ToWhole(color.g);
		this->b = ToWhole(color.b);
		this->a = 255;
	}

	Color::Color(const glm::vec4& color)
	{
		this->r = ToWhole(color.r);
		this->g = ToWhole(color.g);
		this->b = ToWhole(color.b);
		this->a = ToWhole(color.a);
	}

	Color::Color(float r, float g, float b, float a)
	{
		this->r = ToWhole(r);
		this->g = ToWhole(g);
		this->b = ToWhole(b);
		this->a = ToWhole(a);
	}

	SDL_Color Color::GetSDL() const
	{
		return SDL_Color{ r, g, b, a };
	}

	glm::vec4 Color::GetVec() const
	{
		return glm::vec4(
			ToNormalized(r),
			ToNormalized(g),
			ToNormalized(b),
			ToNormalized(a)
		);
	}

	uint8_t Color::ToWhole(float value) const
	{
		return uint8_t(value * 255.0f);
	}

	float Color::ToNormalized(uint8_t value) const
	{
		return float(value) / 255.0f;
	}
}

#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#pragma warning(pop)

#include <SDL.h>

namespace dae
{
	class Color
	{
	public:
		Color(const glm::vec3& color);
		Color(const glm::vec4& color);
		Color(float r, float g, float b, float a = 1.0f);

		SDL_Color GetSDL() const;
		glm::vec4 GetVec() const;

	private:
		uint8_t ToWhole(float value) const;
		float ToNormalized(uint8_t value) const;

	private:
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};
}

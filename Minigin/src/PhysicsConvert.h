#pragma once

#pragma once

#include <box2d/box2d.h>

#pragma warning(push)
#pragma warning(disable:4201)
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class PhysicsConvert final
	{
	public:
		static glm::vec2 ToGlmVec(const b2Vec2& vec);
		static glm::vec3 ToGlmVec(const b2Vec3& vec);

		static b2Vec2 ToBox2DVec(const glm::vec2& vec);
		static b2Vec3 ToBox2DVec(const glm::vec3& vec);
	};
}

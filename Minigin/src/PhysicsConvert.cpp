#include "MiniginPCH.h"
#include "PhysicsConvert.h"

namespace dae
{
	glm::vec2 PhysicsConvert::ToGlmVec(const b2Vec2& vec)
	{
		return glm::vec2(vec.x, vec.y);
	}

	glm::vec3 PhysicsConvert::ToGlmVec(const b2Vec3& vec)
	{
		return glm::vec3(vec.x, vec.y, vec.z);
	}

	b2Vec2 PhysicsConvert::ToBox2DVec(const glm::vec2& vec)
	{
		return b2Vec2(vec.x, vec.y);
	}

	b2Vec3 PhysicsConvert::ToBox2DVec(const glm::vec3& vec)
	{
		return b2Vec3(vec.x, vec.y, vec.z);
	}
}

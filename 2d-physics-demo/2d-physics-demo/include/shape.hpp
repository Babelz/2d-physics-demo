#pragma once

#include "aabb.hpp"

namespace fs 
{
	struct Vector2;

	// Base class for implementing shapes.
	struct Shape 
	{
		float centerOfInertia;
		float mass;

		virtual void calculateInertia() = 0;

		virtual AABB calculateAABB(const Vector2& position, float rotation) const = 0;
	};
}
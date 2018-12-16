#pragma once

#include "aabb.hpp"

namespace fs 
{
	enum ShapeType
	{
		Box    = 0, 
		Circle = 1
	};

	struct Vector2;

	// Base class for implementing shapes.
	struct Shape 
	{
		ShapeType type;

		float momentOfInertia;
		float mass;

		Shape(ShapeType type);

		virtual void calculateInertia() = 0;

		virtual AABB calculateAABB(const Vector2& position, float rotation) const = 0;
	};
}
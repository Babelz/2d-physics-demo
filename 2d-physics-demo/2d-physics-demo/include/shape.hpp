#pragma once

#include "aabb.hpp"
#include "mat2x2.h"

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

		bool isStatic = false;		
		fs::Mat2x2 modelToWorld;

		float momentOfInertia;
		float mass;

		Shape(ShapeType type, fs::Mat2x2 mtw);

		virtual void calculateInertia() = 0;

		virtual AABB calculateAABB(const Vector2& position, float rotation) const = 0;
	};
}
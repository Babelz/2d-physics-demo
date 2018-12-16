#pragma once

#include "shape.hpp"
#include "aabb.hpp"
#include "mat2x2.h"

namespace fs 
{
	// Shape that represents a box that is defined
	// by it's width and height.
	struct BoxShape final : public Shape 
	{
		static unsigned const int VertexCount = 4;

		float width;
		float height;

		fs::Vector2 vertices[4];
		fs::Vector2 normals[4];

		BoxShape(float width, float height);
		BoxShape() = delete;

		fs::Vector2 getSupport(fs::Vector2 direction);

		virtual void calculateInertia() final override;

		virtual AABB calculateAABB(const Vector2& position, float rotation) const final override;
	};
}
#pragma once

#include "shape.hpp"
#include "aabb.hpp"

namespace fs 
{
	// Shape that represents a circle that is defined 
	// by it's radius.
	struct CircleShape final : public Shape 
	{
		float radius;

		virtual void computeIntertia() final;

		virtual AABB calculateAABB(const Vector2& position, float rotation) const final;
	};
}
#pragma once

#include "shape.hpp"
#include "aabb.hpp"

namespace fs 
{
	// Shape that represents a box that is defined
	// by it's width and height.
	struct BoxShape final : public Shape 
	{
		float width;
		float height;

		virtual void computeIntertia() final;

		virtual AABB calculateAABB(const Vector2& position, float rotation) const final;
	};
}
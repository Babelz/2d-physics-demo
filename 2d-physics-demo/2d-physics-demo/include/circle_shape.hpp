#pragma once

#include "shape.hpp"

namespace fs 
{
	// Shape that represents a circle that is defined 
	// by it's radius.
	struct CircleShape final : public Shape 
	{
		float radius;

		virtual void computeIntertia() final;
	};
}
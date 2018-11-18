#pragma once

#include "vector2.hpp"

namespace fs
{
	struct AABB 
	{
		Vector2 min = { 0.0f, 0.0f };
		Vector2 max = { 0.0f, 0.0f };
	};
}
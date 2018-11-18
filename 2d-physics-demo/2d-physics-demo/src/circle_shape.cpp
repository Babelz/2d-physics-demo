#include "circle_shape.hpp"

namespace fs 
{
	void CircleShape::calculateInertia()
	{
		momentOfInertia = mass * radius * radius * 0.5f;
	}

	AABB CircleShape::calculateAABB(const Vector2& position, float rotation) const 
	{
		AABB aabb;

		aabb.min.x = position.x - radius;
		aabb.min.y = position.y - radius;

		aabb.max.x = position.x + radius;
		aabb.max.y = position.y + radius;

		return aabb;
	}
}
#include <math.h>
#include <algorithm>

#include "box_shape.hpp"

namespace fs
{
	void BoxShape::computeIntertia()
	{
		centerOfInertia = mass * (width * width + height * height) / 12.0f;
	}

	AABB BoxShape::calculateAABB(const Vector2& position, float rotation) const
	{
		Vector2 points[4];

		Vector2 origin = Vector2(width * 0.5f, height * 0.5f);

		float sinv = sin(rotation);
		float cosv = cos(rotation);

		points[0].x = (-origin.x * cosv) - (origin.y * sinv);
		points[0].y = (-origin.x * sinv) + (origin.y * cosv);
		points[0] += position;

		points[1].x = (origin.x * cosv) - (origin.y * sinv);
		points[1].y = (origin.x * sinv) + (origin.y * cosv);
		points[1] += position;

		points[2].x = (-origin.x * cosv) - (-origin.y * sinv);
		points[2].y = (-origin.x * sinv) + (-origin.y * cosv);
		points[2] += position;

		points[3].x = (origin.x * cosv) - (-origin.y * sinv);
		points[3].y = (origin.x * sinv) + (-origin.y * cosv);
		points[3] += position;

		float maxx = std::max_element(std::begin(points), std::end(points), [&](const Vector2& first, const Vector2& second) {
			return first.x > second.x;
		})->x;
		
		float maxy = std::max_element(std::begin(points), std::end(points), [&](const Vector2& first, const Vector2& second) {
			return first.y > second.y;
		})->y;
		
		float minx = std::min_element(std::begin(points), std::end(points), [&](const Vector2& first, const Vector2& second) {
			return first.x < second.x;
		})->x;

		float miny = std::min_element(std::begin(points), std::end(points), [&](const Vector2& first, const Vector2& second) {
			return first.y < second.y;
		})->y;

		AABB aabb;

		aabb.min = Vector2(minx, miny);
		aabb.max = Vector2(maxx, maxy);

		return aabb;
	}
}
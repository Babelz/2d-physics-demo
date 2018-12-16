#include <math.h>
#include <algorithm>

#include "box_shape.hpp"

namespace fs
{
	BoxShape::BoxShape(float width, float height)
		: Shape(ShapeType::Box, fs::Mat2x2(1.0f, 0.0f, 0.0f, 1.0f))
	{
		// Bottom-left corner.
		vertices[0] = fs::Vector2(width / -2, height / -2);
		// Bottom-right corner.
		vertices[1] = fs::Vector2(width / 2, height / -2);
		// Top-right corner.
		vertices[2] = fs::Vector2(width / 2, height / 2);
		// Top-left corner.
		vertices[3] = fs::Vector2(width / -2, height / 2);

		// Bottom normal.
		normals[0] = fs::Vector2(0.0f, -1.0f);
		// Right normal.
		normals[1] = fs::Vector2(1.0f, 0.0f);
		// Up normal.
		normals[2] = fs::Vector2(0.0f, 1.0f);
		// Left normal.
		normals[3] = fs::Vector2(-1.0f, 0.0f);
	}

	void BoxShape::calculateInertia()
	{
		momentOfInertia = mass * (width * width + height * height) / 12.0f;
	}

	fs::Vector2 BoxShape::getSupport(fs::Vector2 direction)
	{
		float bestProjection   = -FLT_MAX;
		fs::Vector2 bestVertex = Vector2::zero;

		for (unsigned i = 0; i < VertexCount; i++)
		{
			fs::Vector2& vertex = vertices[i];
			float projection    = Vector2::dot(vertex, direction);

			if (projection > bestProjection)
			{
				bestVertex     = vertex;
				bestProjection = projection;
			}
		}

		return bestVertex;
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
			return first.x < second.x;
		})->x;
		
		float maxy = std::max_element(std::begin(points), std::end(points), [&](const Vector2& first, const Vector2& second) {
			return first.y < second.y;
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
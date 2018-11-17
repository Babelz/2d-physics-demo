#pragma once

#include "vector2.hpp"
#include "aabb.hpp"

namespace fs
{
	struct Shape;

	// Rigid body that is defined by velocities, forces
	// and it's shape.
	struct RigidBody final
	{
		Vector2 position;
		Vector2 linearVelocity;
		Vector2 force;

		float rotation;
		float angularVelocity;
		float torque;

		AABB aabb;

		Shape* const shape;

		RigidBody(Shape* const shape);

		void calculateAABB();

		~RigidBody();
	};
}
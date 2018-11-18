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
		Vector2 position       = { 0.0f, 0.0f };
		Vector2 linearVelocity = { 0.0f, 0.0f };
		Vector2 force		   = { 0.0f, 0.0f };

		float rotation		  = 0.0f;
		float angularVelocity = 0.0f;
		float torque		  = 0.0f;

		AABB aabb = { { 0.0f, 0.0f }, { 0.0f, 0.0f } };

		Shape* const shape = nullptr;

		RigidBody(Shape* const shape);

		void calculateAABB();

		~RigidBody();
	};
}
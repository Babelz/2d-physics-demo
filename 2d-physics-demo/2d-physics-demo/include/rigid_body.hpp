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

		float restitution;
		float rotation;
		float angularVelocity;
		float torque;

		AABB aabb;

		Shape* const shape;

		RigidBody(Shape* const shape);

		void applyForce(const fs::Vector2& force);
		void applyImpulse(const fs::Vector2& impulse, const fs::Vector2& contact);

		void calculateAABB();

		~RigidBody();
	};
}
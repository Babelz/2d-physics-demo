#include <cassert>

#include "rigid_body.hpp"
#include "shape.hpp"

namespace fs
{
	RigidBody::RigidBody(Shape* const shape)
		: shape(shape),
	      position(fs::Vector2::zero),
	      linearVelocity(fs::Vector2::zero),
		  force(fs::Vector2::zero),
		  rotation(0.0f),
		  angularVelocity(0.0f),
		  torque(0.0f),
		  restitution(0.0f)
	{
		assert(shape != nullptr);
	}

	void RigidBody::applyForce(const fs::Vector2& force)
	{
		this->force += force;
	}
	void RigidBody::applyImpulse(const fs::Vector2& impulse, const fs::Vector2& contact)
	{
		linearVelocity += impulse * (1.0f / shape->mass);

		angularVelocity += Vector2::cross(contact, impulse) * (1.0f / shape->momentOfInertia);
	}

	void RigidBody::calculateAABB()
	{
		aabb = shape->calculateAABB(position, rotation);
	}

	RigidBody::~RigidBody()
	{
		delete shape;
	}
}
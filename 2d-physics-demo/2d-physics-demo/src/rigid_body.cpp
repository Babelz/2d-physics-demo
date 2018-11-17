#include <cassert>

#include "rigid_body.hpp"
#include "shape.hpp"

namespace fs
{
	RigidBody::RigidBody(Shape* const shape) 
		: shape(shape) 
	{
		assert(shape != nullptr);
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
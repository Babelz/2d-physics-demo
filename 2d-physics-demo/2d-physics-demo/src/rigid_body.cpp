#include <cassert>

#include "rigid_body.hpp"

namespace fs
{
	RigidBody::RigidBody(Shape* const shape) 
		: shape(shape) 
	{
		assert(shape != nullptr);
	}

	RigidBody::~RigidBody()
	{
		delete shape;
	}
}
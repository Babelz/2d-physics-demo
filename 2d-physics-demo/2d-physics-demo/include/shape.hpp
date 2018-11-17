#pragma once

namespace fs 
{
	// Base class for implementing shapes.
	struct Shape 
	{
		float centerOfInertia;
		float mass;

		virtual void calculateInertia() = 0;
	};
}
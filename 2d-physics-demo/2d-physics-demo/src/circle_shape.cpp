#include "circle_shape.hpp"

namespace fs 
{
	void CircleShape::computeIntertia()
	{
		centerOfInertia = mass * radius * radius * 0.5f;
	}
}
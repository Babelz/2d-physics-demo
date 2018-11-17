#include "box_shape.hpp"

namespace fs
{
	void BoxShape::computeIntertia() 
	{
		centerOfInertia = mass * (width * width + height * height) / 12.0f;
	}
}
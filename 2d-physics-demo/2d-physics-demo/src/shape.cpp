#include "shape.hpp"

namespace fs
{
	Shape::Shape(ShapeType type, fs::Mat2x2 mtw)
		: type(type), modelToWorld(mtw)
	{
	}
}
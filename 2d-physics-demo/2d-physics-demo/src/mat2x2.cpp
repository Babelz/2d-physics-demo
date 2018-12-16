#include "..\include\mat2x2.h"

#include <cmath>

namespace fs
{
	Mat2x2::Mat2x2(float radians) 
	{
		rotate(radians);
	}
	Mat2x2::Mat2x2(float a, float b, float c, float d)
		: m11(a), m12(b), m21(c), m22(d)
	{
	}

	void Mat2x2::rotate(float radians)
	{
		float c = std::cos(radians);
		float s = std::sin(radians);

		m11 = c; 
		m12 = -s;
		m21 = s;
		m22 = c;
	}
}
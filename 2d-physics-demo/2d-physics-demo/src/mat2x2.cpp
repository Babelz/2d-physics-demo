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

	Mat2x2 operator*(const Mat2x2& a, const Mat2x2& b)
	{
		return Mat2x2
		{
			a[0][0] * b[0][0] + a[0][1] * b[1][0],
			a[0][0] * b[0][1] + a[0][1] * b[1][1],
			a[1][0] * b[0][0] + a[1][1] * b[1][0],
			a[1][0] * b[0][1] + a[1][1] * b[1][1]
		};
	}
	fs::Vector2 operator*(const Mat2x2& m, const fs::Vector2& v)
	{
		return fs::Vector2
		{
			m[0][0] * v[0] + m[0][1] * v[1],
			m[1][0] * v[0] + m[1][1] * v[1]
		};
	}
}
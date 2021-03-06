#include <math.h>

#include "vector2.hpp"

namespace fs 
{
	Vector2 const Vector2::unitx = Vector2(1.0f, 0.0f);
	Vector2 const Vector2::unity = Vector2(0.0f, 1.0f);
	Vector2 const Vector2::zero  = Vector2(0.0f);
	Vector2 const Vector2::one   = Vector2(1.0f);

	Vector2::Vector2(float x, float y) 
		: x(x), y(y) 
	{
	}
	Vector2::Vector2(float xy) 
		: x(xy), y(xy) 
	{
	}
	Vector2::Vector2() 
		: Vector2(0.0f) 
	{
	}

	Vector2& Vector2::operator +=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2& Vector2::operator -=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	Vector2& Vector2::operator *=(const Vector2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;

		return *this;
	}

	Vector2& Vector2::operator *=(float value)
	{
		x *= value;
		y *= value;

		return *this;
	}

	bool Vector2::operator ==(const Vector2& rhs) const 
	{
		return x == rhs.x &&
			   y == rhs.y;
	}
	bool Vector2::operator !=(const Vector2& rhs) const 
	{
		return !(*this == rhs);
	}

	float Vector2::cross(const Vector2& a, const Vector2& b)
	{
		return a.x * b.y - b.x * a.y;
	}

	float Vector2::dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	float Vector2::length(const Vector2& vec)
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	Vector2 Vector2::normalize(const Vector2& vec)
	{
		float length       = Vector2::length(vec);
		float inverse	   = 1.0f / length;
		fs::Vector2 result = fs::Vector2(0.0f);

		result.x = vec.x * inverse;
		result.y = vec.y * inverse;
	
		return result;
	}


	Vector2 operator +(Vector2 lhs, const Vector2& rhs)
	{
		lhs += rhs;

		return lhs;
	}
	Vector2 operator -(Vector2 lhs, const Vector2& rhs)
	{
		lhs -= rhs;

		return lhs;
	}
	Vector2 operator *(Vector2 lhs, const Vector2& rhs)
	{
		lhs *= rhs;

		return lhs;
	}
	Vector2 operator *(Vector2 vector, float value)
	{
		vector *= value;

		return vector;
	}

	Vector2 operator *(float value, Vector2 vector)
	{
		vector *= value;

		return vector;
	}
}
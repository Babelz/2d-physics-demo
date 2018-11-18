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

	Vector2 Vector2::operator +(const Vector2& rhs) const 
	{
		Vector2 result;

		result.x = x + rhs.x;
		result.y = y + rhs.y;

		return result;
	}
	Vector2 Vector2::operator -(const Vector2& rhs) const 
	{
		Vector2 result;

		result.x = x - rhs.x;
		result.y = y - rhs.y;

		return result;
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

	Vector2 Vector2::operator *(const Vector2& rhs) const 
	{
		Vector2 result;

		result.x = x * rhs.x;
		result.y = y * rhs.y;

		return result;
	}
	Vector2& Vector2::operator *=(const Vector2& rhs) 
	{
		x *= rhs.x;
		y *= rhs.y;

		return *this;
	}

	Vector2 Vector2::operator *(float value) const 
	{
		Vector2 result;

		result.x = x * value;
		result.y = y * value;

		return result;
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
}
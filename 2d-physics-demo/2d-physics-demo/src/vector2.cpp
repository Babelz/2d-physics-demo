#include "vector2.hpp"

namespace fs {

	Vector2 const Vector2::unitx = Vector2(1.0f, 0.0f);
	Vector2 const Vector2::unity = Vector2(0.0f, 1.0f);
	Vector2 const Vector2::zero  = Vector2(0.0f);

	Vector2::Vector2(float x, float y) : x(x), y(y) {
	}
	Vector2::Vector2(float xy) : x(xy), y(xy) {
	}
	Vector2::Vector2() : Vector2(0.0f) {
	}

	Vector2 Vector2::operator +(const Vector2& rhs) const {
		Vector2 result;

		result.x = x + rhs.x;
		result.y = y + rhs.y;

		return result;
	}
	Vector2 Vector2::operator -(const Vector2& rhs) const {
		Vector2 result;

		result.x = x - rhs.x;
		result.y = y - rhs.y;

		return result;
	}
	Vector2& Vector2::operator +=(const Vector2& rhs) {
		x += rhs.x;
		y += rhs.y;

		return *this;
	}
	Vector2& Vector2::operator -=(const Vector2& rhs) {
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	Vector2 Vector2::operator *(const Vector2& rhs) const {
		Vector2 result;

		result.x = x * rhs.x;
		result.y = y * rhs.y;

		return result;
	}
	Vector2& Vector2::operator *=(const Vector2& rhs) {
		x *= rhs.x;
		y *= rhs.y;

		return *this;
	}

	Vector2 Vector2::operator *(float value) const {
		Vector2 result;

		result.x = x * value;
		result.y = y * value;

		return result;
	}
	Vector2& Vector2::operator *=(float value) {
		x *= value;
		y *= value;

		return *this;
	}

	bool Vector2::operator ==(const Vector2& rhs) const {
		return x == rhs.x &&
			   y == rhs.y;
	}
	bool Vector2::operator !=(const Vector2& rhs) const {
		return !(*this == rhs);
	}
}
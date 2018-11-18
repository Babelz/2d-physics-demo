#pragma once

namespace fs 
{
	struct Vector2 final 
	{
		static Vector2 const unitx;
		static Vector2 const unity;
		static Vector2 const zero;
		static Vector2 const one;

		float x;
		float y;

		Vector2(float x, float y);
		Vector2(float xy);
		Vector2();

		Vector2& operator +=(const Vector2& rhs);
		Vector2& operator -=(const Vector2& rhs);
		Vector2& operator *=(const Vector2& rhs);
		Vector2& operator *=(float value);

		bool operator ==(const Vector2& rhs) const;
		bool operator !=(const Vector2& rhs) const;

		static float cross(const Vector2& a, const Vector2& b);
		static float dot(const Vector2& a, const Vector2& b);
		static float length(const Vector2& vec);
	};

	Vector2 operator +(Vector2 lhs, const Vector2& rhs);
	Vector2 operator -(Vector2 lhs, const Vector2& rhs);
	Vector2 operator *(Vector2 lhs, const Vector2& rhs);
	Vector2 operator *(Vector2 vector, float value);
}
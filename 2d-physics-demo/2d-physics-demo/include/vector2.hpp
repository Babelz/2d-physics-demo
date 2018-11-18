#pragma once

namespace fs 
{
	// Simple 2-component vector with x and y components.
	struct Vector2 final 
	{
		// X-unit vector with x component set to 1 and y to 0.
		static Vector2 const unitx;
		
		// Y-unit vector with y component set to 1 and x to 0.
		static Vector2 const unity;

		// Zero vector with all it's components set to 0.
		static Vector2 const zero;

		float x;
		float y;

		Vector2(float x, float y);
		Vector2(float xy);
		Vector2();

		Vector2 operator +(const Vector2& rhs) const;
		Vector2 operator -(const Vector2& rhs) const;

		Vector2& operator +=(const Vector2& rhs);
		Vector2& operator -=(const Vector2& rhs);

		Vector2 operator *(const Vector2& rhs) const;
		Vector2& operator *=(const Vector2& rhs);

		Vector2 operator *(float value) const;
		Vector2& operator *=(float value);

		bool operator ==(const Vector2& rhs) const;
		bool operator !=(const Vector2& rhs) const;

		static float Cross(const Vector2& a, const Vector2& b);
	};
}
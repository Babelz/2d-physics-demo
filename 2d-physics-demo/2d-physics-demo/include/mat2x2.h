#pragma once

#include "vector2.hpp"

namespace fs
{
	struct Mat2x2 final
	{
		union
		{
			struct 
			{
				float m11, m12;
				float m21, m22;
			};

			struct
			{
				fs::Vector2 x;
				fs::Vector2 y;
			};

			fs::Vector2 mat[2];
		};

		Mat2x2(float radians);
		Mat2x2(float a, float b, float c, float d);
		
		void rotate(float radians);
	
		fs::Vector2& operator[](unsigned int index) 
		{ 
			return mat[index];
		}
		
		const fs::Vector2& operator[](unsigned int index) const
		{ 
			return mat[index]; 
		}
	};

	Mat2x2 operator*(const Mat2x2& a, const Mat2x2& b);
	fs::Vector2 operator*(const Mat2x2& m, const fs::Vector2& v);
}
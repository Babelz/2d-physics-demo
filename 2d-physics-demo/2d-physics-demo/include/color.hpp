#pragma once

#include <inttypes.h>

namespace fs
{
	struct Color final 
	{
		static Color const black;
		static Color const white;
		static Color const red;
		static Color const green;
		static Color const blue;

		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		Color();

		bool operator ==(const Color& rhs) const;
		bool operator !=(const Color& rhs) const;
	};
}
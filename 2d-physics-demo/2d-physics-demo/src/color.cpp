#include "color.hpp"

namespace fs
{
	Color const Color::black = Color(0, 0, 0, 255);
	Color const Color::white = Color(255, 255, 255, 255);
	Color const Color::red   = Color(255, 0, 0, 255);
	Color const Color::green = Color(0, 255, 0, 255);
	Color const Color::blue  = Color(0, 0, 255, 255);

	Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) 
		: r(r), g(g), b(b), a(a)
	{
	}

	Color::Color() 
		: r(0u), g(0u), b(0u), a(0u) 
	{
	}

	bool Color::operator ==(const Color& rhs) const 
	{
		return r == rhs.r &&
			   g == rhs.g &&
			   b == rhs.b &&
			   a == rhs.a;
	}
	bool Color::operator !=(const Color& rhs) const 
	{
		return !(*this == rhs);
	}
}
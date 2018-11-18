#include <iostream>
#include <cassert>

#include "vector2.hpp"
#include "color.hpp"
#include "convert_units.hpp"

#include "window.hpp"

void convertUnitsTests() 
{
	fs::setScreenUnitToWorldUnitRatio(32.0f);

	// Test converting from world units to screen units.
	assert(fs::toScreenUnits(0.5f) == 16.0f);
	assert(fs::toScreenUnits(1.0f) == 32.0f);
	assert(fs::toScreenUnits(10.0f) == 320.0f);

	// Test converting from screen units to world units.
	assert(fs::toWorldUnits(16.0f) == 0.5f);
	assert(fs::toWorldUnits(32.0f) == 1.0f);
	assert(fs::toWorldUnits(320.0f) == 10.0f);
}

void vector2Tests() 
{
	assert(fs::Vector2::unitx.x == 1.0f);
	assert(fs::Vector2::unitx.y == 0.0f);

	assert(fs::Vector2::unity.x == 0.0f);
	assert(fs::Vector2::unity.y == 1.0f);

	assert(fs::Vector2::zero.x == 0.0f);
	assert(fs::Vector2::zero.y == 0.0f);

	assert(fs::Vector2(1.0f) + fs::Vector2(1.0f) == fs::Vector2(2.0f));
	assert(fs::Vector2(1.0f) - fs::Vector2(1.0f) == fs::Vector2(0.0f));
	assert(fs::Vector2(2.0f) * fs::Vector2(2.0f) == fs::Vector2(4.0f));

	assert(fs::Vector2(1.0f) == fs::Vector2(1.0f));
	assert(fs::Vector2(1.0f) != fs::Vector2(0.0f));
}

int main() 
{
	// Run tests.
	convertUnitsTests();
	
	vector2Tests();

	fs::Window window = fs::Window("physics-demo-2d", 1280, 720);

	float r = 0.0f;

	for (;;) 
	{
		if (!window.isOpen()) break;
		
		r += 0.1f;

		// Do updates.
		window.poll();
	
		// Do drawing.
		window.begin();
		
		//for (size_t i = 0; i < 64; i++)
		//{
		//	for (size_t j = 0; j < 64; j++)
		//	{
		//		window.rectangle(fs::Vector2(32.0f * i, 32.0f * j), fs::Vector2(32.0f), fs::Vector2(16.0f), r, fs::Color::red);
		//	}
		//}

		float yf = 0.0f;

		for (size_t i = 0; i < 10; i++)
		{
			float xf = 0.0f;
			
			for (size_t j = 0; j < 10; j++)
			{
				window.circle(fs::Vector2(j * 32.0f + 200.0f + xf, i * 32.0f + 200.0f + yf), 32.0f, fs::Color::green);
			
				xf += 32.0f;
			}

			yf += 32.0f;
		}

		window.end();
	}

	return 0;
}
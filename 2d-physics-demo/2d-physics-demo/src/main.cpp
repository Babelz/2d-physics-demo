#include <iostream>
#include <cassert>

#include "vector2.hpp"
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

	for (;;) 
	{
		if (!window.isOpen()) break;
		
		window.poll();
	}

	return 0;
}
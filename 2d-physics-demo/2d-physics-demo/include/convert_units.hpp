#pragma once


namespace fs {
	// Contains utilities that help converting values between 
	// screen and world spaces.

	struct Vector2;

	// Sets the ratio for converting units from screen units to world
	// units and back.
	void setScreenUnitToWorldUnitRatio(float screenUnitsPerWorldUnit);

	// Converts given world units to screen units.
	float toScreenUnits(float worldUnits);

	// Converts given vector value from world units
	// to screen units.
	Vector2 toScreenUnits(Vector2& worldUnits);

	// Converts given screen units to world units.
	float toWorldUnits(float screenUnits);

	// Converts given vector value from screen units
	// to world units.
	Vector2 toWorldUnits(Vector2& screenUnits);
}
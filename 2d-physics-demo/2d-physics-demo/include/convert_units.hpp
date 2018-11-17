#pragma once

namespace fs {

	class Vector2;

	void setScreenUnitToWorldUnitRatio(float screenUnitsPerWorldUnit);

	float toScreenUnits(float worldUnits);
	Vector2 toScreenUnits(Vector2& worldUnits);

	float toWorldUnits(float screenUnits);
	Vector2 toWorldUnits(Vector2& screenUnits);
}
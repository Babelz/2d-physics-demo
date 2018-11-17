#include "convert_units.hpp"
#include "vector2.hpp"

namespace fs 
{
	float screenUnitsToWorldUnitsRatio;
	float worldUnitsToScreenUnitsRatio;
	
	void setScreenUnitToWorldUnitRatio(float screenUnitsPerWorldUnit) 
	{
		screenUnitsToWorldUnitsRatio = screenUnitsPerWorldUnit;
		worldUnitsToScreenUnitsRatio = 1.0f / screenUnitsPerWorldUnit;
	}

	float toScreenUnits(float worldUnits) 
	{
		return worldUnits * screenUnitsToWorldUnitsRatio;
	}
	Vector2 toScreenUnits(Vector2& worldUnits) 
	{
		Vector2 vector;
		
		vector.x = worldUnits.x * screenUnitsToWorldUnitsRatio;
		vector.y = worldUnits.y * screenUnitsToWorldUnitsRatio;
	
		return vector;
	}

	float toWorldUnits(float screenUnits) 
	{
		return screenUnits * worldUnitsToScreenUnitsRatio;
	}
	Vector2 toWorldUnits(Vector2& screenUnits) 
	{
		Vector2 vector;

		vector.x = screenUnits.x * worldUnitsToScreenUnitsRatio;
		vector.y = screenUnits.y * worldUnitsToScreenUnitsRatio;

		return vector;
	}
}
#pragma once

namespace fs
{
	bool biasGreaterThan(float a, float b) 
	{
		const float relative = 0.95f;
		const float absolute = 0.01f;
	
		return a >= b * relative + a * absolute;
	}
}
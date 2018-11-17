#include <iostream>

#include "convert_units.hpp"

int main() {
	fs::setScreenUnitToWorldUnitRatio(32.0f);

	std::cout << fs::toScreenUnits(0.5f) << std::endl;
	std::cout << fs::toScreenUnits(1.0f) << std::endl;
	std::cout << fs::toScreenUnits(10.0f) << std::endl << std::endl;

	std::cout << fs::toWorldUnits(16.0f) << std::endl;
	std::cout << fs::toWorldUnits(32.0f) << std::endl;
	std::cout << fs::toWorldUnits(320.0f) << std::endl;

	system("pause");

	return 0;
}
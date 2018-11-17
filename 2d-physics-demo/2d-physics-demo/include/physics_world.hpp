#pragma once

#include "vector2.hpp"
#include "rigid_body.hpp"
#include <vector>

class PhysicsWorld
{
public:
	PhysicsWorld(float stepsPerSecond);

	void setPhysicsRate(float stepsPerSecond);
	float getPhysicsRate();

	void step(float delta);

private:
	float updateRate;
	float stepTime;
	std::vector<fs::RigidBody*> bodyArray;

};
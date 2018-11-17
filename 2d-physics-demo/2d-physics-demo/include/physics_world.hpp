#pragma once

#include "vector2.hpp"
#include "rigid_body.hpp"
#include <vector>

struct SweepPair
{
	float location;
	fs::RigidBody* body;
};

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
	std::vector<SweepPair> sweepPairArray;
	std::vector<std::pair<fs::RigidBody*, fs::RigidBody*>> collisionPairs;
	std::vector<fs::RigidBody*> activeBodies;

	bool comparePairs(SweepPair* a, SweepPair* b);
};
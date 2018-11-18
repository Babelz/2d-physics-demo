#pragma once

#include "vector2.hpp"
#include "rigid_body.hpp"
#include "aabb.hpp"

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
	std::vector<fs::RigidBody*> bodyArray;

private:
	float updateRate;
	float stepTime;

	std::vector<SweepPair> sweepPairArray;
	std::vector<fs::RigidBody*> activeBodies;
	std::vector<std::pair<fs::RigidBody*, fs::RigidBody*>> testPairs;
	std::vector<std::pair<fs::RigidBody*, fs::RigidBody*>> collidingPairs;

	bool testAABBOverlap(fs::AABB* a, fs::AABB* b);
};
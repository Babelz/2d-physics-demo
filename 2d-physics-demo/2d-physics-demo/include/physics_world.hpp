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
	fs::Vector2 gravity = fs::Vector2(0.0f, 9.81f);

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
	void circleToCircle(fs::RigidBody* a, fs::RigidBody* b);
	void circleToBox(fs::RigidBody* a, fs::RigidBody* b);
	void boxToBox(fs::RigidBody* a, fs::RigidBody* b);
};
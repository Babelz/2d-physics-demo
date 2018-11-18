#include "physics_world.hpp"
#include "shape.hpp"
#include "circle_shape.hpp"
#include "box_shape.hpp"

#include <functional>
#include <algorithm>

PhysicsWorld::PhysicsWorld(float stepsPerSecond)
{
	updateRate = stepsPerSecond;
}

void PhysicsWorld::setPhysicsRate(float stepsPerSecond)
{
	updateRate = stepsPerSecond;
}
float PhysicsWorld::getPhysicsRate()
{
	return updateRate;
}

void PhysicsWorld::step(float delta)
{
	stepTime = stepTime + delta;

	if (stepTime >= (1.0f / updateRate))
	{
		// Apply forces and torques to objects
		for (unsigned int i = 0; i < bodyArray.size(); i++)
		{
			// bodyArray[i]->force = fs::Vector2(1.0f * 0.001f) * fs::Vector2::unity;
		}

		// Update object locations, velocities and rotations
		for (unsigned int i = 0; i < bodyArray.size(); i++)
		{
			fs::RigidBody* updateBody = bodyArray[i];
			// Calculate linear acceleration
			fs::Vector2 linearAcceleration;
			linearAcceleration.x = (updateBody->force.x / updateBody->shape->mass);
			linearAcceleration.y = (updateBody->force.y / updateBody->shape->mass);
			
			// Update velocity for each axis
			updateBody->linearVelocity.x += linearAcceleration.x * stepTime;
			updateBody->linearVelocity.y += linearAcceleration.y * stepTime;

			// Update position for each axis
			updateBody->position.x += updateBody->linearVelocity.x * stepTime;
			updateBody->position.y += updateBody->linearVelocity.y * stepTime;

			// Calculate angular acceleration
			float angularAcceleration = updateBody->torque / updateBody->shape->mass;

			// Update angular velocity
			updateBody->angularVelocity += angularAcceleration * stepTime;

			// Update object rotation
			updateBody->rotation += updateBody->angularVelocity * stepTime;

			// Update object AABB
			updateBody->calculateAABB();
		}

		// DETECT COLLISIONS
		// Add all min and max x-values to an array with their bodies
		unsigned int pairIndex = 0;
		sweepPairArray.reserve(bodyArray.size() * 2);

		for (unsigned int i = 0; i < bodyArray.size(); i++)
		{
			sweepPairArray.push_back(SweepPair());
			sweepPairArray[pairIndex].location = bodyArray[i]->aabb.min.x;
			sweepPairArray[pairIndex].body = bodyArray[i];
			pairIndex++;

			sweepPairArray.push_back(SweepPair());
			sweepPairArray[pairIndex].location = bodyArray[i]->aabb.max.x;
			sweepPairArray[pairIndex].body = bodyArray[i];
			pairIndex++;
		}
		
		// Sort the pair list by the x-value
		std::sort(sweepPairArray.begin(), sweepPairArray.end(), [](const SweepPair& a, const SweepPair& b)
		{
			return (a.location < b.location);
		});
		
		// Go through sorted array (SWEEP AND PRUNE)
		unsigned int sweepIndex = 0;
		while (sweepIndex < sweepPairArray.size())
		{
			// Add first (a) to active list
			activeBodies.push_back(sweepPairArray[sweepIndex].body);
			
			//// If a.maxx is met before b.minx, remove from active list, add b to active list
			if (sweepIndex + 1 < sweepPairArray.size())
			{
				if (activeBodies[sweepIndex] == sweepPairArray[sweepIndex + 1].body)
				{
					activeBodies.erase(std::begin(activeBodies) + sweepIndex);
					sweepPairArray.erase(std::begin(sweepPairArray) + sweepIndex + 1);

					continue;
				}
				else
				{
					activeBodies.push_back(sweepPairArray[sweepIndex + 1].body);
					sweepIndex++;
				}
			}
			else 
			{
				sweepIndex++;
			}


			//If there are active bodies, add pair (a,b) to check collisions list
			if (activeBodies.size() >= 2)
			{
				for (unsigned int i = 0; i < activeBodies.size(); i++)
				{
					for (unsigned int j = (i + 1); j < activeBodies.size(); j++)
					{
						std::pair<fs::RigidBody*, fs::RigidBody*> collisionPair = std::make_pair(activeBodies[i], activeBodies[j]);
						testPairs.push_back(collisionPair);
					}
				}
			}
			// Continue until list is iterated through
		}
	
		//TODO Remove duplicates from collision pairs

		// Test AABB Overlaps and add overlapping pairs to final collision check list
		for (unsigned int i = 0; i < testPairs.size(); i++)
		{
			if (testAABBOverlap(&testPairs[i].first->aabb, &testPairs[i].second->aabb))
			{
				collidingPairs.push_back((testPairs[i]));
			}
		}
		
		for (unsigned int i = 0; i < collidingPairs.size(); i++)
		{
			// Calculate contacts and apply impulses
			if (dynamic_cast<fs::CircleShape*>(collidingPairs[i].first->shape) != nullptr &&
				dynamic_cast<fs::CircleShape*>(collidingPairs[i].second->shape) != nullptr)
			{
				circleToCircle(collidingPairs[i].first, collidingPairs[i].second);
			}
		}

		// Solve collisions

		stepTime = 0.0f;
	
		sweepPairArray.clear();
		activeBodies.clear();
		testPairs.clear();
		collidingPairs.clear();
	}	
}

bool PhysicsWorld::testAABBOverlap(fs::AABB* a, fs::AABB* b)
{
	float test_x1 = b->min.x - a->max.x;
	float test_y1 = b->min.y - a->max.y;
	
	float test_x2 = a->min.x - b->max.x;
	float test_y2 = a->min.y - b->max.y;
	
	// AABB's overlap if the differences between
	// min and max values are less than zero.
	
	if (test_x1 > 0.0f || test_y1 > 0.0f)
		return false;	// No overlap
	
	if (test_x2 > 0.0f || test_y2 > 0.0f)
		return false;	// No overlap
	
	return true;
}

void PhysicsWorld::circleToCircle(fs::RigidBody* a, fs::RigidBody* b)
{
	fs::Vector2 relativeVelocity = b->linearVelocity - a->linearVelocity;
	fs::Vector2 normalVector = b->position - a->position;

	float normalVelocity = fs::Vector2::dot(relativeVelocity, normalVector);

	if (normalVelocity > 0)
		return;

	float smallerRestitution = std::min(a->restitution, b->restitution);

	float impulseScalar = -(1 + smallerRestitution) * normalVelocity;
	impulseScalar /= 1 / a->shape->mass + 1 / b->shape->mass;

	// TODO Get contact point
	fs::Vector2 impulse = normalVector * impulseScalar;
	a->applyImpulse(fs::Vector2(-1.0f) * impulse, a->position);
	b->applyImpulse(impulse, b->position);
}

void PhysicsWorld::circleToBox(fs::RigidBody* a, fs::RigidBody* b)
{
}

void PhysicsWorld::boxToBox(fs::RigidBody* a, fs::RigidBody* b)
{
}

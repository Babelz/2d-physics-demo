#include "physics_world.hpp"
#include "shape.hpp"

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
			// Compute force and torque
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
		}

		// Detect collisions
		// Add all min and max x-values to an array with their bodies
		unsigned int pairIndex = 0;
		sweepPairArray.reserve(bodyArray.size() * 2);
		for (unsigned int i = 0; i < bodyArray.size(); i++)
		{
			sweepPairArray[pairIndex].location = bodyArray[i]->aabb.min.x;
			sweepPairArray[pairIndex].body = bodyArray[i];
			pairIndex++;

			sweepPairArray[pairIndex].location = bodyArray[i]->aabb.max.x;
			sweepPairArray[pairIndex].body = bodyArray[i];
			pairIndex++;
		}
		
		// Sort the pair list by the x-value
		std::sort(sweepPairArray.begin(), sweepPairArray.end(), [](const SweepPair& a, const SweepPair& b)
		{
			return (a.location < b.location);
		});
		
		// Go through sorted array
		unsigned int sweepIndex = 0;
		while (sweepIndex < sweepPairArray.size())
		{
			// Add first (a) to active list
			activeBodies[sweepIndex] = sweepPairArray[sweepIndex].body;

			// If a.maxx is met before b.minx, remove from active list, add b to active list
			if (sweepIndex + 1 < sweepPairArray.size())
			{
				if (activeBodies[sweepIndex] == sweepPairArray[sweepIndex + 1].body)
				{
					activeBodies.erase(std::begin(activeBodies) + sweepIndex);
					sweepIndex += 2;
					continue;
				}
				else
				{
					activeBodies[sweepIndex + 1] = sweepPairArray[sweepIndex + 1].body;
				}
			}

			//If there are active bodies, add pair (a,b) to check collisions list
			if (activeBodies.size() >= 2)
			{
				for (unsigned int i = 0; i < activeBodies.size(); i++)
				{
					for (unsigned int j = (i + 1); j < activeBodies.size(); j++)
					{
						std::pair<fs::RigidBody*, fs::RigidBody*> collisionPair = std::make_pair(activeBodies[i], activeBodies[j]);
						collisionPairs.push_back(collisionPair);
					}
				}
			}
			// Continue until list is iterated through
		}
	
		// Remove duplicates from collision pairs
		// Solve collisions

		stepTime = 0.0f;
	}

}
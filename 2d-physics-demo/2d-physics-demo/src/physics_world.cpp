#include "physics_world.hpp"
#include "shape.hpp"

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
		for (int i = 0; i < bodyArray.size(); i++)
		{
			// Compute force and torque
		}

		// Update object locations, velocities and rotations
		for (int i = 0; i < bodyArray.size(); i++)
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


		// Solve collisions

		stepTime = 0.0f;
	}

}

#include "physics_world.hpp"
#include "shape.hpp"
#include "circle_shape.hpp"
#include "box_shape.hpp"
#include "math.hpp"

#include <iostream>
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
			// Check collisions and calculate impulses
			if (collidingPairs[i].first->shape->type == fs::ShapeType::Circle &&
				collidingPairs[i].second->shape->type == fs::ShapeType::Circle)
			{
				// Circle to Circle.
				circleToCircle(collidingPairs[i].first, collidingPairs[i].second);
			}
			else if (collidingPairs[i].first->shape->type == fs::ShapeType::Circle &&
				     collidingPairs[i].second->shape->type == fs::ShapeType::Box)
			{
				// Circle to Box.
				circleToBox(collidingPairs[i].first, collidingPairs[i].second);
			}
			else if (collidingPairs[i].first->shape->type == fs::ShapeType::Box &&
				     collidingPairs[i].second->shape->type == fs::ShapeType::Circle)
			{
				// Box to Circle.
				circleToBox(collidingPairs[i].second, collidingPairs[i].first);
			}
			else if (collidingPairs[i].first->shape->type == fs::ShapeType::Box &&
				     collidingPairs[i].second->shape->type == fs::ShapeType::Box)
			{
				// Box to Box.
				boxToBox(collidingPairs[i].first, collidingPairs[i].second);
			}
		}

		// Solve collisions
		for (auto body : bodyArray)
		{
			body->force = fs::Vector2::zero;
			body->torque = 0.0f;
		}

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
	fs::CircleShape* aShape = dynamic_cast<fs::CircleShape*>(a->shape);
	fs::CircleShape* bShape = dynamic_cast<fs::CircleShape*>(b->shape);

	float radiusSum = aShape->radius + bShape->radius;
	float positionDifference = fs::Vector2::length(a->position - b->position);

	if (radiusSum < positionDifference)
		return;

	fs::Vector2 relativeVelocity = b->linearVelocity - a->linearVelocity;
	fs::Vector2 normalVector = b->position - a->position;

	float normalVelocity = fs::Vector2::dot(relativeVelocity, normalVector);

	if (normalVelocity > 0)
		return;

	float smallerRestitution = std::min(a->restitution, b->restitution);

	float impulseScalar = -(1 + smallerRestitution) * normalVelocity;

	impulseScalar = impulseScalar / (1 / a->shape->mass + 1 / b->shape->mass);

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
	fs::BoxShape* aShape = dynamic_cast<fs::BoxShape*>(a->shape);
	fs::BoxShape* bShape = dynamic_cast<fs::BoxShape*>(b->shape);

	// Find a->b penetration.
	unsigned int faceA = 0u;
	float penetrationA = 0.0f;

	fs::findAxisLeastPenetration(&faceA, &penetrationA, a, b);

	// No penetration.
	if (penetrationA >= 0.0f) return;

	// Find b->a penetration.
	unsigned int faceB = 0u;
	float penetrationB = 0.0f;

	fs::findAxisLeastPenetration(&faceB, &penetrationB, b, a);

	// No penetration.
	if (penetrationB >= 0.0f) return;

	unsigned int referenceIndex = 0u;
	bool shouldFlip			    = false;

	fs::BoxShape* referencedBox = nullptr;
	fs::BoxShape* incidentBox   = nullptr;

	if (fs::biasGreaterThan(penetrationA, penetrationB))
	{
		referencedBox  = aShape;
		incidentBox    = bShape;
		referenceIndex = faceA;
		shouldFlip     = false;
	}
	else 
	{
		referencedBox  = bShape;
		incidentBox    = aShape;
		referenceIndex = faceB;
		shouldFlip     = true;
	}

	// Compute and find faces.
	fs::Vector2 incidentFace[2];

	fs::findIncidentFace(incidentFace, a, b, referenceIndex);

	fs::Vector2 vertex1 = aShape->vertices[referenceIndex];

	referenceIndex = referenceIndex + 1 == aShape->VertexCount ? 0 : referenceIndex + 1;

	fs::Vector2 vertex2 = aShape->vertices[referenceIndex];

	// Transform to world.
	vertex1 = aShape->modelToWorld * vertex1 + a->position;
	vertex2 = aShape->modelToWorld * vertex2 + a->position;

	fs::Vector2 sidePlaneNormal = vertex2 - vertex1;
	sidePlaneNormal             = fs::Vector2::normalize(sidePlaneNormal);

	fs::Vector2 referenceFaceNormal = { sidePlaneNormal[1], -sidePlaneNormal[0] };

	float referenceDistance = fs::Vector2::dot(referenceFaceNormal, vertex1);
	float negativeSide      = -fs::Vector2::dot(sidePlaneNormal, vertex1);
	float positiveSide      = fs::Vector2::dot(sidePlaneNormal, vertex2);

	if (fs::clip(sidePlaneNormal * -1.0f, negativeSide, incidentFace) < 2) return;
	if (fs::clip(sidePlaneNormal, positiveSide, incidentFace) < 2)		   return;

	// Respond.
	fs::Vector2 intersectionNormal = shouldFlip ? referenceFaceNormal * -1.0f : referenceFaceNormal;
	
	float penetration = 0.0f;
	
	fs::Vector2 contacts[2];

	unsigned int clippedPoints = 0u;
	float separation		   = fs::Vector2::dot(referenceFaceNormal, incidentFace[0]) - referenceDistance;

	if (separation <= 0.0f)
	{
		contacts[clippedPoints] = incidentFace[0];
		penetration			    = -separation;
		
		clippedPoints++;
	}
	else
	{
		penetration = 0.0f;
	}

	separation = fs::Vector2::dot(referenceFaceNormal, incidentFace[1]) - referenceDistance;

	if (separation <= 0.0f)
	{
		contacts[clippedPoints] = incidentFace[1];
		penetration				-= separation;
	
		clippedPoints++;

		penetration /= float(clippedPoints);
	}

	unsigned int contactCount = clippedPoints;

	for (unsigned int i = 0u; i < contactCount; i++)
	{
		fs::Vector2 radiusA = contacts[i] - a->position;
		fs::Vector2 radiusB = contacts[i] - b->position;

		fs::Vector2 relativeVelocity = b->linearVelocity + fs::Vector2::cross(b->angularVelocity, radiusB) - 
									   a->angularVelocity - fs::Vector2::cross(a->angularVelocity, radiusA);
	
		float contactVelocity = fs::Vector2::dot(relativeVelocity, intersectionNormal);

		if (contactVelocity > 0) return;

		float radiusACrossN  = fs::Vector2::cross(radiusA, intersectionNormal);
		float radiusBCrossN  = fs::Vector2::cross(radiusB, intersectionNormal);
		float inverseMassSum = (1.0f / aShape->mass) + (1.0f / bShape->mass);

		// paskana???
		inverseMassSum += radiusACrossN * radiusACrossN * (1.0f / aShape->momentOfInertia);
		inverseMassSum += radiusBCrossN * radiusBCrossN * (1.0f / bShape->momentOfInertia);

		// Impulse scalar.
		float impulseScalar = -(1.0f + std::min(a->restitution, b->restitution)) * contactVelocity;

		impulseScalar /= inverseMassSum;
		impulseScalar /= float(contactCount);

		// Apply impulse.
		fs::Vector2 impulseVector = intersectionNormal * impulseScalar;

		a->applyImpulse(impulseVector * -1.0f, radiusA);
		b->applyImpulse(impulseVector, radiusB);
	}
}

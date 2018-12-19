#include <iostream>
#include <cassert>
#include <vector>
#include <chrono>
#include <inttypes.h>
#include <windows.h>

#include "rigid_body.hpp"
#include "box_shape.hpp"
#include "circle_shape.hpp"
#include "vector2.hpp"
#include "color.hpp"
#include "convert_units.hpp"
#include "physics_world.hpp"

#include "window.hpp"

bool showAABB = true;

PhysicsWorld world = PhysicsWorld(60.0f);

struct BodyGroup final 
{
	std::vector<fs::RigidBody*> bodies;
	std::vector<fs::Color> colors;
};

BodyGroup groups[2];

const uint8_t GROUP_BOXES   = 0;
const uint8_t GROUP_CIRCLES = 1;

fs::RigidBody* createBox(float x, float y, float width, float height, float mass, fs::Color color, bool isStatic = false) 
{
	fs::BoxShape* shape = new fs::BoxShape(width, height);

	shape->isStatic = isStatic;
	shape->width    = width;
	shape->height   = height;
	shape->mass     = mass;

	fs::RigidBody* body = new fs::RigidBody(shape);

	body->position.x = x;
	body->position.y = y;

	groups[GROUP_BOXES].bodies.push_back(body);
	groups[GROUP_BOXES].colors.push_back(color);

	world.bodyArray.push_back(body);
	
	shape->calculateInertia();
	shape->calculateAABB(body->position, body->rotation);

	return body;
}

fs::RigidBody* createCircle(float x, float y, float radius, float mass, fs::Color color)
{
	fs::CircleShape* shape = new fs::CircleShape();

	shape->radius = radius;
	shape->mass   = mass;

	shape->calculateInertia();

	fs::RigidBody* body = new fs::RigidBody(shape);

	body->position.x = x;
	body->position.y = y;
	
	groups[GROUP_CIRCLES].bodies.push_back(body);
	groups[GROUP_CIRCLES].colors.push_back(color);

	world.bodyArray.push_back(body);

	return body;
}

int main() 
{
	fs::setScreenUnitToWorldUnitRatio(2.0f);

	fs::Window window = fs::Window("physics-demo-2d", 1280, 720);

	float oy = 200.f;

	for (int i = 0; i < 2; i++)
	{
		float ox = 128.f;
		
		for (int j = 0; j < 2; j++)
		{
			auto* box = createBox(j * 1.0f + ox , i * 2.0f + oy, 20.0f, 32.0f, 10.0f, fs::Color::red);
		
			ox += 32.0f;

			box->applyForce(fs::Vector2((float)9000.f, 0.0f));
		}

		oy += 32.0f;
	}

	oy = 250.f;

	for (int i = 0; i < 2; i++)
	{
		float ox = 512.0f;

		for (int j = 0; j < 2; j++)
		{
			auto* box = createBox(j * 3.0f + ox, i * 3.0f + oy, 20.0f, 32.0f, 10.0f, fs::Color::red);

			ox += 32.0f;

			box->applyForce(fs::Vector2((float)-9000.f, 0.0f));
		}

		oy += 32.0f;
	}

	auto current = std::chrono::high_resolution_clock::now();
	auto last    = std::chrono::high_resolution_clock::now();

	for (;;)
	{
		if (!window.isOpen()) break;
		
		// Update delta.
		last    = current;
		current = std::chrono::high_resolution_clock::now();

		std::chrono::duration<float> elapsed = current - last;

		// Update world.
		world.step(elapsed.count());

		// Do updates.
		window.poll();

		// Do drawing.
		window.begin();

		// Draw boxes.
		for (uint32_t i = 0; i < groups[GROUP_BOXES].bodies.size(); i++)
		{
			fs::RigidBody* body = groups[GROUP_BOXES].bodies[i];
			fs::BoxShape* shape = dynamic_cast<fs::BoxShape*>(body->shape);

			// Draw the rect.
			window.rectangle(fs::toScreenUnits(body->position),
							 fs::toScreenUnits(fs::Vector2(shape->width, shape->height)),
							 fs::toScreenUnits(fs::Vector2(shape->width, shape->height) * 0.5f),
							 body->rotation,
							 groups[GROUP_BOXES].colors[i]);
		}

		// Draw circles.
		for (uint32_t i = 0; i < groups[GROUP_CIRCLES].bodies.size(); i++)
		{
			fs::RigidBody* body    = groups[GROUP_CIRCLES].bodies[i];
			fs::CircleShape* shape = dynamic_cast<fs::CircleShape*>(body->shape);

			// Draw the circle.
			window.circle(fs::toScreenUnits(body->position),
						  fs::toScreenUnits(shape->radius),
						  groups[GROUP_CIRCLES].colors[i]);
		}

		if (showAABB)
		{
			// Draw circle aabbs.
			for (uint32_t i = 0; i < groups[GROUP_CIRCLES].bodies.size(); i++)
			{
				fs::RigidBody* body = groups[GROUP_CIRCLES].bodies[i];
				fs::CircleShape* shape = dynamic_cast<fs::CircleShape*>(body->shape);

				// Draw aabb.
				fs::AABB& aabb = body->aabb;

				window.rectangleEdges(fs::toScreenUnits(body->position) - fs::toScreenUnits(fs::Vector2(shape->radius, shape->radius)),
					fs::toScreenUnits(aabb.max - aabb.min),
					fs::toScreenUnits(aabb.max - aabb.min) * 0.5f,
					0.0f,
					fs::Color::red);
			}

			// Draw box aabbs.
			for (uint32_t i = 0; i < groups[GROUP_BOXES].bodies.size(); i++)
			{
				fs::RigidBody* body = groups[GROUP_BOXES].bodies[i];
				fs::BoxShape* shape = dynamic_cast<fs::BoxShape*>(body->shape);

				// Draw aabb.
				fs::AABB& aabb = body->aabb;

				window.rectangleEdges(fs::toScreenUnits(body->position) + (fs::toScreenUnits(fs::Vector2(shape->width, shape->height)) - fs::toScreenUnits(aabb.max - aabb.min)) * 0.5f,
					fs::toScreenUnits(aabb.max - aabb.min),// + (fs::toScreenUnits(aabb.max - aabb.min) - fs::toScreenUnits(fs::Vector2(shape->width, shape->height))),
					fs::toScreenUnits(aabb.max - aabb.min) * 0.5f,
					0.0f,
					fs::Color::red);
			}
		}

		window.end();
	}

	return 0;
}
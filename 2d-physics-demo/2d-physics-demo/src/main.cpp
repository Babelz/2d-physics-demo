#include <iostream>
#include <cassert>
#include <vector>
#include <inttypes.h>

#include "rigid_body.hpp"
#include "box_shape.hpp"
#include "circle_shape.hpp"
#include "vector2.hpp"
#include "color.hpp"
#include "convert_units.hpp"
#include "physics_world.hpp"

#include "window.hpp"

PhysicsWorld world = PhysicsWorld(30.0f);

struct BodyGroup final 
{
	std::vector<fs::RigidBody*> bodies;
	std::vector<fs::Color> colors;
};

BodyGroup groups[2];

const uint8_t GROUP_BOXES   = 0;
const uint8_t GROUP_CIRCLES = 1;

fs::RigidBody* createBox(float x, float y, float width, float height, float mass, fs::Color color) 
{
	fs::BoxShape* shape = new fs::BoxShape();

	shape->width  = width;
	shape->height = height;
	shape->mass   = mass;

	shape->calculateInertia();

	fs::RigidBody* body = new fs::RigidBody(shape);

	body->position.x = x;
	body->position.y = y;

	groups[GROUP_BOXES].bodies.push_back(body);
	groups[GROUP_BOXES].colors.push_back(color);

	world.bodyArray.push_back(body);
	
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
	fs::setScreenUnitToWorldUnitRatio(32.0f);

	fs::Window window = fs::Window("physics-demo-2d", 1280, 720);

	createBox(10.0f, 10.0f, 1.0f, 1.0f, 0.0f, fs::Color::green);
	createBox(12.0f, 10.0f, 1.0f, 1.0f, 0.0f, fs::Color::red);
	createBox(14.0f, 10.0f, 1.0f, 1.0f, 0.0f, fs::Color::blue);

	for (;;)
	{
		if (!window.isOpen()) break;

		world.step(0.0333f);

		// Do updates.
		window.poll();

		// Do drawing.
		window.begin();

		// Draw boxes.
		for (uint32_t i = 0; i < groups[GROUP_BOXES].bodies.size(); i++)
		{
			fs::RigidBody* body = groups[GROUP_BOXES].bodies[i];
			fs::BoxShape* shape = dynamic_cast<fs::BoxShape*>(body->shape);

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

			window.circle(fs::toScreenUnits(body->position),
						  fs::toScreenUnits(shape->radius),
						  groups[GROUP_CIRCLES].colors[i]);
		}

		window.end();
	}

	return 0;
}
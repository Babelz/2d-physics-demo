#include <cassert>

#include <SDL.h>
#include <math.h>

#include "window.hpp"
#include "color.hpp"
#include "vector2.hpp"

#include "third-party/sdl_gfx/SDL2_gfxPrimitives.h"

namespace fs
{
	Window::Window(const char* title, uint16_t width, uint16_t height) 
		: open(true)
	{
		assert(title != NULL);
		assert(width > 0);
		assert(height > 0);

		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

		window   = SDL_CreateWindow(title, width / 2, height / 2, width, height, 0);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		empty	 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 1, 1);
	
		uint8_t pixels[] = { 255, 255, 255, 255 };

		SDL_UpdateTexture(empty, NULL, &pixels, 4);
	}
	
	bool Window::isOpen() const 
	{
		return open;
	}

	void Window::begin() 
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		
		SDL_RenderClear(renderer);
	}

	void Window::end()
	{
		SDL_RenderPresent(renderer);
	}

	void Window::rectangle(const Vector2& position, const Vector2& size, const Vector2& origin, float rotation, const Color& color)
	{
		SDL_Rect destination;

		destination.x = (int)floor(position.x);
		destination.y = (int)floor(position.y);
		destination.w = (int)floor(size.x);
		destination.h = (int)floor(size.y);

		SDL_Point center;

		center.x = (int)floor(origin.x);
		center.y = (int)floor(origin.y);

		SDL_SetTextureColorMod(empty, color.r, color.g, color.b);
		
		SDL_RenderCopyEx(renderer,
						 empty,
			             NULL,
						 &destination,
						 (rotation * 180.0f) / M_PI,
					     &center,
						 SDL_FLIP_NONE);
	}

	void Window::rectangleEdges(const Vector2& position, const Vector2& size, const Vector2& origin, float rotation, const Color& color)
	{
		fs::Vector2 points[4];

		// Top left.
		points[0] = position;

		// Top right.
		points[1] = position + fs::Vector2::unitx * size.x;

		// Bottom right.
		points[2] = position + size;

		// Bottom left.
		points[3] = position + fs::Vector2::unity * size.y;

		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

		// Top left to top right.
		SDL_RenderDrawLine(renderer, ((int)floor(points[0].x)), ((int)floor(points[0].y)), ((int)floor(points[1].x)), ((int)floor(points[1].y)));
		
		// Top right to bottom right.
		SDL_RenderDrawLine(renderer, ((int)floor(points[1].x)), ((int)floor(points[1].y)), ((int)floor(points[2].x)), ((int)floor(points[2].y)));

		// Bottom right to bottom left.
		SDL_RenderDrawLine(renderer, ((int)floor(points[2].x)), ((int)floor(points[2].y)), ((int)floor(points[3].x)), ((int)floor(points[3].y)));
		
		// Bottom left to top left.
		SDL_RenderDrawLine(renderer, ((int)floor(points[3].x)), ((int)floor(points[3].y)), ((int)floor(points[0].x)), ((int)floor(points[0].y)));
	}

	void Window::circle(const Vector2& position, const float radius, const Color& color)
	{
		filledCircleRGBA(renderer, (short)(floor(position.x)), (short)(floor(position.y)), (short)(floor(radius)), color.r, color.g, color.b, color.a);
	}

	void Window::poll()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_KEYDOWN:
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) open = false;
				break;
			case SDL_QUIT:
				open = false;
				break;
			default:
				break;
			}
		}
	}

	void Window::close()
	{
		open = false;
	}

	Window::~Window()
	{
		SDL_DestroyWindow(window);
	}
}
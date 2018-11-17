#include <cassert>

#include <SDL.h>

#include "window.hpp"
#include "color.hpp"
#include "vector2.hpp"

namespace fs
{
	Window::Window(const char* title, uint16_t width, uint16_t height) 
		: open(true)
	{
		assert(title != NULL);
		assert(width > 0);
		assert(height > 0);

		window = SDL_CreateWindow(title, width / 2, height / 2, width, height, 0);
	}
	
	bool Window::isOpen() const 
	{
		return open;
	}

	void Window::rectangle(const Vector2& position, const Vector2& size, const Vector2& origin, const Color& color)
	{
	}

	void Window::circle(const Vector2& position, const float radius, const Color& color)
	{
	}

	void Window::poll()
	{
		for (;;) {
			if (!open) break;

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
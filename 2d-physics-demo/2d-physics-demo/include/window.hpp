#pragma once

#include <inttypes.h>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace fs 
{
	struct Vector2;
	struct Color;

	// Class that represents a window and presents it as a canvas
	// for simple rendering operations.
	class Window final
	{
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;

		SDL_Texture* empty;

		bool open;
	public:
		Window(const char* title, uint16_t width, uint16_t height);

		bool isOpen() const;

		// Poll for window events.
		void poll();

		// Closes the window.
		void close();

		// Begins rendering operations.
		void begin();

		// Draws rectangle to the window using given presentation parameters.
		void rectangle(const Vector2& position, const Vector2& size, const Vector2& origin, float rotation, const Color& color);
		
		// Draws circle to the window using given presentation parameters.
		void circle(const Vector2& position, const float radius, const Color& color);

		// Ends rendering operations.
		void end();

		~Window();
	};
}
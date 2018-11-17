#pragma once

namespace fs 
{
	class Window final
	{
	private:

	public:
		void drawRectangle(float px, float py, float w, float h, float ox, float oy, float rotation);
		void drawCircle(float px, float py, float r, float ox, float oy, float rotation);
	};
}
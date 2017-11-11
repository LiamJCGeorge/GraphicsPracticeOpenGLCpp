#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

namespace Engine {
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4, RESIZABLE = 0x8 };

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
		void swapBuffer();

		int getScreenWidth() { _screenWidth; }
		int getScreenHeight() { _screenHeight; }

		SDL_Window* getWindow() { return _sdlwindow; }
	private:
		SDL_Window* _sdlwindow;
		int _screenWidth, _screenHeight;
	};
}

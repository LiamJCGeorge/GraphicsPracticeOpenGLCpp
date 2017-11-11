#include "Window.h"
#include "Errors.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Engine {
	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;

		Uint32 flags = SDL_WINDOW_OPENGL; //default

		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}
		if (currentFlags & RESIZABLE) {
			flags |= SDL_WINDOW_RESIZABLE;
		}

		_sdlwindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (_sdlwindow == nullptr) {
			fatalError("SDL Window could not be created!");
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlwindow);
		if (glContext == nullptr) {
			fatalError("SDL_Gl Context could not be created!");
		}

		GLenum error = glewInit();
		if (error != GLEW_OK) {
			fatalError("Could not initialize glew!");
		}
		//print OpenGL Version
		printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

		glClearDepth(1.0);
		glClearColor(0.35f, 0.35f, 0.35f, 1.0f);

		// set VSYNC
		SDL_GL_SetSwapInterval(0);
		
		// pick different blend modes in future
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0; // error code
	}

	void Window::swapBuffer() {
		SDL_GL_SwapWindow(_sdlwindow);
	}
}

/*
case SDL_WINDOWEVENT: // testing
if (evnt.window.event == SDL_WINDOWEVENT_RESIZED)
{
SDL_Window* win = SDL_GetWindowFromID(evnt.window.windowID);
if (win == _window)
{

_screenWidth  = evnt.window.data1;
_screenHeight = evnt.window.data2;
glViewport(0, 0, _screenWidth, _screenHeight);

_solidProgram.use();
_proj = glm::perspective(glm::radians(45.0f), (float)(_screenWidth / _screenHeight), 0.1f, 1000.0f);
glUniformMatrix4fv(_solidProgram.projLocation, 1, GL_FALSE, &_proj[0][0]);
_solidProgram.unuse();
}
*/
#include <SDL/SDL.h>
#include <Gl/glew.h>

#include "Engine.h"

namespace Engine {

	int init() {
		//initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);


		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// hide mouse and prevent it from leaving the screen while in focus
		SDL_SetRelativeMouseMode(SDL_TRUE);

		return 0;
	}
}
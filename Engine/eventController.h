#pragma once

#include <vector>
#include <functional>
#include <SDL\SDL.h>

namespace Engine {
	namespace eventController {

		typedef std::function< void(void) > funcType;
		typedef std::vector < std::function<void(void)>> evntList;
		typedef const void(*classFunc)(void);

		enum Evnt { WINDOW, MOUSEMOTION, QUIT, _w, _a, _s, _d, _tab, _esc  };

		SDL_Keycode getKey();

		void handleEvent(funcType fn, Evnt etype);

		// interclass communication
		SDL_Event createMessage(int code);

		void fireMessage(SDL_Event &e);

		void catchMessage(funcType fn);

		void run();

	}
}
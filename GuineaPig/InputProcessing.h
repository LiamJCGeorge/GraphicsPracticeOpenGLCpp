#pragma once

#include <vector>
#include <functional>
#include <SDL\SDL.h>

namespace eventController {

	typedef SDL_Event eventParam;
	typedef std::function< void(eventParam) > funcType;
	typedef std::vector < std::function<void(eventParam)>> evntList;
	typedef void(*classFunc)(eventParam);
	
	enum Evnt { WINDOW, MOUSE, KEY, QUIT };

	void handleEvent(funcType fn, Evnt etype);

	// interclass communication
	SDL_Event createMessage(int code);

	void fireMessage(SDL_Event &e);

	void catchMessage(funcType fn);

	void run();
	
}
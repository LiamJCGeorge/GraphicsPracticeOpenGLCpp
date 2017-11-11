#include "eventController.h"
#include "InputManager.h"

namespace Engine {
	namespace eventController {

		namespace { //private

			InputManager im;
			SDL_Event _evnt;
			SDL_Keycode _keyCode;

			evntList _window;
			evntList _mouse;
			evntList _key;
			evntList _quit;
			evntList _internal;

			inline void callList(evntList elist) {
				for (std::vector<funcType>::iterator it = elist.begin(); it != elist.end(); ++it)
					(*it)();
			}
		}

		SDL_Keycode getKey() {
			return _keyCode;
		}

		void handleEvent(funcType fn, Evnt etype) {
			switch (etype) {
			case WINDOW: _window.push_back(fn);		break;
			case MOUSEMOTION: _mouse.push_back(fn);	break;
			case KEY: _key.push_back(fn);			break;
			case QUIT: _quit.push_back(fn);			break;
			}
		}

		// TODO
		SDL_Event createMessage(int code) {
			SDL_Event user_event;
			user_event.type = SDL_USEREVENT;
			user_event.user.code = code;
			return user_event;
		}

		// TODO
		void fireMessage(SDL_Event &e) {
			SDL_PushEvent(&e);
		}

		// TODO
		void catchMessage(funcType fn) {
			_internal.push_back(fn);
		}

		void run() {
			while (SDL_PollEvent(&_evnt)) {
				switch (_evnt.type)
				{
				case SDL_KEYDOWN:
					_keyCode = _evnt.key.keysym.sym;
					im.pressKey(_keyCode);
															break;
				case SDL_KEYUP:
					_keyCode = _evnt.key.keysym.sym;
					im.releaseKey(_keyCode);
															break;
				case SDL_MOUSEMOTION: callList(_mouse);		break;
				case SDL_USEREVENT:	  callList(_internal);	break;
				case SDL_WINDOWEVENT: callList(_window);		break;
				case SDL_QUIT:		  callList(_quit);		break;
				}
			}
		}

	}
}

#include "InputManager.h"



namespace Engine {

	InputManager::InputManager() : _mouseCoords(0)
	{}

	void InputManager::pressKey(unsigned int keyCode) {
		_keyMap[keyCode] = true;
	}

	void InputManager::releaseKey(unsigned int keyCode) {
		_keyMap[keyCode] = false;
	}

	void InputManager::setMouseCoords(float x, float y) {
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

	bool InputManager::isKeyPressed(unsigned int keyCode) {
		auto it = _keyMap.find(keyCode);
		if (it != _keyMap.end()) {
			return it->second;
		}
		else {
			return false;
		}
	}

}

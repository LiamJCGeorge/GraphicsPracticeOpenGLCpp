#pragma once
#include <unordered_map>
#include <glm/glm.hpp>

namespace Engine {
	class InputManager
	{
	public:
		InputManager();

		void pressKey(unsigned int keyCode);
		void releaseKey(unsigned int keyCode);
		
		void setMouseCoords(float x, float y);
		glm::vec2 getMouseCoords() const { return _mouseCoords; }

		bool isKeyPressed(unsigned int keyCode);

	private:
		std::unordered_map<unsigned int, bool> _keyMap;
		glm::vec2 _mouseCoords;
	};

}
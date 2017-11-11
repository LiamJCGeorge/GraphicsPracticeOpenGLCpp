#pragma once
#include <GL/glew.h>
#include "GLTexture.h"

#include <string>

namespace Engine {
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void draw();
		void init(float x, float y, float width, float height, std::string texturePath);
		void poll();

	private:
		float _x;
		float _y;
		float _width;
		float _height;
		GLuint _vboID;
		GLTexture _texture;
	};
}

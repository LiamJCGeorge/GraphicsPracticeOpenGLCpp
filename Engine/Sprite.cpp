
#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <iostream>
#include <cstddef>

namespace Engine {
	Sprite::Sprite() : _vboID(0)
	{}


	Sprite::~Sprite()
	{
		if (_vboID == 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}

	void Sprite::draw()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::init(float x, float y, float width, float height, std::string texturePath)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResourceManager::getTexture(texturePath);

		if (_vboID == 0) {
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[12];

		// first triangle
		vertexData[0].setPos(_x + width, _y + height);
		vertexData[0].setUV(1.0f, 1.0f);
		//vertexData[0].setColor(255, 0,0);


		vertexData[1].setPos(_x, _y + height);
		vertexData[1].setUV(0.0f, 1.0f);
		//vertexData[1].setColor(255, 0, 0);


		vertexData[2].setPos(_x, _y);
		vertexData[2].setUV(0.0f, 0.0f);
		//vertexData[2].setColor(255, 0, 0);


		// second triangle
		vertexData[3].setPos(_x, _y);
		vertexData[3].setUV(0.0f, 1.0f);
		//vertexData[3].setColor(255, 0, 0);


		vertexData[4].setPos(_x + width, _y);
		vertexData[4].setUV(1.0f, 0.0f);
		//vertexData[4].setColor(255, 0, 0);


		vertexData[5].setPos(_x + width, _y + height);
		vertexData[5].setUV(1.0f, 1.0f);
		//vertexData[5].setColor(255, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void Sprite::poll() {
		std::cout << ":x,y" + std::to_string(_x) + ", " + std::to_string(_y) + "VBO " + std::to_string(_vboID) << std::endl;
	}
}
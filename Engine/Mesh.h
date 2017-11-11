#pragma once
#include "ResourceManager.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>


namespace Engine {
	struct VertexMesh {
		glm::vec3 Position;

		struct Color {
			GLubyte r;
			GLubyte g;
			GLubyte b;
			GLubyte a;

			Color() : r(0), g(0), b(0), a(0) {}
			Color(GLubyte r, GLubyte g, GLubyte b) : r(r), g(g), b(b), a(255) {}
		}color;

		struct UV {
			float u;
			float v;
			UV() : u(0), v(0) {}
			UV(float u, float v) : u(u), v(v) {}
		}uv;

		VertexMesh& setPos(float x, float y, float z) {
			Position = glm::vec3(x, y, z);
			return *this;
		}

		VertexMesh& setColor(float r, float g, float b) {
			color.r = r;
			color.g = g;
			color.b = b;
			return *this;
		}

		VertexMesh& setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
			return *this;
		}

		VertexMesh() {}
		VertexMesh(glm::vec3 p, float u = 0, float v = 0, GLubyte r = 255, GLubyte g = 255, GLubyte b = 255) : Position(p), uv(UV(u, v)), color(Color(r, g, b)) {}

	};



	class Mesh {
	public:
		/*  Mesh Data  */
		std::vector<VertexMesh> vertices;
		std::vector<GLuint> indices;
		GLTexture texture;
		GLuint VAO;

		Mesh(std::vector<VertexMesh> vertices, std::vector<GLuint> indices, std::string texturePath)
		{
			this->vertices = vertices;
			this->indices = indices;
			texture = ResourceManager::getTexture(texturePath);

			setupMesh();
		}


		void draw()
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture.id);


			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

	private:

		GLuint VBO, EBO;

		void setupMesh()
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexMesh), &vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexMesh), (void*)offsetof(VertexMesh, Position));

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexMesh), (void*)offsetof(VertexMesh, color));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexMesh), (void*)offsetof(VertexMesh, uv));

			glBindVertexArray(0);
		}
	};
}
#pragma once
#include "Camera.h"

#include <string>
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <vector>

namespace Engine {
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragShaderFilePath);

		void linkShaders();

		void addAttribute(const std::string& attributeName);

		void use();

		void unuse();

		void setInt(const std::string &uniformName, int value) const;
		void setBool(const std::string &name, bool value) const;
		void setFloat(const std::string &name, float value) const;

		GLuint programID;
		GLuint modelLocation;
		GLuint projLocation;
		GLuint viewLocation;

	private:
		void compileShader(const std::string& filePath, GLuint shaderID);

		int _numAttributes;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

	};


}
#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine {
	GLSLProgram::GLSLProgram() : _numAttributes(0), programID(0), _vertexShaderID(0), _fragmentShaderID(0)
	{

	}


	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::use() {
		glUseProgram(programID);
		for (int i = 0; i < _numAttributes; i++) {
			glEnableVertexAttribArray(i);
		}
		// run through queue of functions that need to be called while program is in use
			// camera hook - camera method checks and updates view uniform variable
	}


	void GLSLProgram::unuse() {
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}

	void GLSLProgram::compileShaders(const std::string & vertexShaderFilePath, const std::string & fragmentShaderFilePath)
	{
		programID = glCreateProgram();

		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0) {
			fatalError("vertex shader failed to be created!");
		}
		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0) {
			fatalError("fragment shader failed to be created!");
		}

		compileShader(vertexShaderFilePath, _vertexShaderID);
		compileShader(fragmentShaderFilePath, _fragmentShaderID);



	}

	void GLSLProgram::linkShaders()
	{
		//Vertex and fragment shaders are successfully compiled.
		//Now time to link them together into a program.

		//Attach our shaders to our program
		glAttachShader(programID, _vertexShaderID);
		glAttachShader(programID, _fragmentShaderID);

		//Link our program
		glLinkProgram(programID);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

			//We don't need the program anymore.
			glDeleteProgram(programID);
			//Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			//Use the infoLog as you see fit.

			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to link!");

		}

		modelLocation = glGetUniformLocation(programID, "model");
		projLocation = glGetUniformLocation(programID, "proj");
		viewLocation = glGetUniformLocation(programID, "view");


		//Always detach shaders after a successful link.
		glDetachShader(programID, _vertexShaderID);
		glDetachShader(programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	void GLSLProgram::addAttribute(const std::string& attributeName) {
		glBindAttribLocation(programID, _numAttributes++, attributeName.c_str());
	}


	void GLSLProgram::compileShader(const std::string& filePath, GLuint shaderID) {
		std::ifstream vertexFile(filePath);
		if (vertexFile.fail()) {
			perror(filePath.c_str());
			fatalError("Failed to open" + filePath);
		}

		std::string fileContents = "";
		std::string line;

		while (std::getline(vertexFile, line)) {
			fileContents += line + "\n";
		}

		vertexFile.close();

		const char* contentsPtr = fileContents.c_str();
		glShaderSource(shaderID, 1, &contentsPtr, nullptr);

		glCompileShader(shaderID);

		GLint success = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(shaderID); // Don't leak the shader.

			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader" + filePath + "failed to compile!");
		}



	}

	void GLSLProgram::setBool(const std::string &name, bool value) const {
		glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
	}

	void GLSLProgram::setInt(const std::string& uniformName, int value) const {
		glUniform1i(glGetUniformLocation(programID, uniformName.c_str()), value);
	}

	void GLSLProgram::setFloat(const std::string &name, float value) const {
		glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
	}
}

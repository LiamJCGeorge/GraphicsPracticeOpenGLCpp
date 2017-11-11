#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"
#include "stb_image.h"
#include <iostream>

namespace Engine {
	GLTexture ImageLoader::loadPNG(std::string filePath) {
		GLTexture texture = {};

		std::vector<unsigned char> in;
		std::vector<unsigned char> out;

		unsigned long width, height;

		if (IOManager::readFileToBuffer(filePath, in) == false) {
			fatalError("Failed to load PNG file to buffer!");
		}

		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
		if (errorCode != 0) {
			fatalError("decodePNG failed with error: " + std::to_string(errorCode));
		}


		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		//target, mipmap, savedformat, width, height, border, incomingFormat, type of data coming in, pointer to actual data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
		glGenerateMipmap(GL_TEXTURE_2D);

		//texture attributes
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;
		return texture;
	}

	GLTexture ImageLoader::loadJPEG(std::string filePath) {
		GLTexture texture = {};

		std::vector<char> v(filePath.begin(), filePath.end());
		v.push_back('\0'); // Make sure we are null-terminated
		char* c = &v[0];

		stbi_set_flip_vertically_on_load(true);
		int width, height, nrChannels;
		unsigned char *data = stbi_load(c, &width, &height, &nrChannels, 0);
		if (data == NULL) {
			fatalError("Failed to load JPEG file!");
		}

		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);

		//target, mipmap, savedformat, width, height, border, incomingFormat, type of data coming in, pointer to actual data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//new
		glGenerateMipmap(GL_TEXTURE_2D);

		//texture attributes
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);

		texture.width = width;
		texture.height = height;
		return texture;

	}
}

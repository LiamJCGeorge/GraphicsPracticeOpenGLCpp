#pragma once
#include <map>
#include "GLTexture.h"

namespace Engine {
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string);

	private:
		std::map<std::string, GLTexture> _textureMap;
	};
}

#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace Engine {
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath) {

		//lookuop texture and see if its in the map
		auto mit = _textureMap.find(texturePath);

		//check if its not in the map
		if (mit == _textureMap.end()) {
			// load it in
			GLTexture newTexture;
			char type = texturePath[texturePath.length() - 2];
			switch (type) {
			case 'n': // PNG
				newTexture = ImageLoader::loadPNG(texturePath);
				break;
			case 'p': // JPEG
				newTexture = ImageLoader::loadJPEG(texturePath);
				break;
			}
			//insert into map
			_textureMap.insert(make_pair(texturePath, newTexture));

			std::cout << "Loaded Texture!\n";
			return newTexture;
		}
		std::cout<< "Used Cached Texture!\n";
		return mit->second;

	}
}
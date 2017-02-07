#include "TextureCache.h"

#include "ImageLoader.h"
#include<iostream>

namespace Gamegine {
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}




	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		//std::map<std::string,GLTexture> --> could be replaced by auto,only work for long type case,but not  for int etc.

		auto mit = _textureMap.find(texturePath);

		//check if it's not in the map
		if (mit == _textureMap.end())
		{
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//insert it into map
			_textureMap.insert(make_pair(texturePath, newTexture));

			std::cout << "Used cache texture \n ";
			return newTexture;
		}

		std::cout << "Loaded texture \n ";
		return mit->second;
	}

}
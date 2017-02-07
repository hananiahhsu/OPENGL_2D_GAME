#pragma once
#include "GLTexture.h"
#include<map>
#include<string>

namespace Gamegine {
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string texturePath);


	private:
		//use the map structure to store textures(png,jpg etc)
		std::map<std::string, GLTexture> _textureMap;
	};

}
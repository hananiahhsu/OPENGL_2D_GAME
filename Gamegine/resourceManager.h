#pragma once
#include "TextureCache.h"

namespace Gamegine {
	class resourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);
		static GLuint boundTexture;
	private:
		static TextureCache _textureCache;
	};

}
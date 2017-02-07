#include "resourceManager.h"

namespace Gamegine {
	TextureCache resourceManager::_textureCache;
	GLTexture resourceManager::getTexture(std::string texturePath)
	{
		return _textureCache.getTexture(texturePath);
	}

}
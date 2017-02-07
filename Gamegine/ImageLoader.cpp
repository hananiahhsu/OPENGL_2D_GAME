#include "ImageLoader.h"

#include "picoPNG.h"
#include<vector>
#include "Errors.h"
#include "IOManager.h"

namespace Gamegine {
	GLTexture ImageLoader::loadPNG(const std::string& filePath)
	{
		GLTexture texture = {};

		std::vector<unsigned char> in;
		std::vector<unsigned char> out;

		unsigned long width, height;

		//load the png image
		if (IOManager::readFileToBuffer(filePath, in) == false)
		{
			fatalError("Failed to load png to buffer!");
		}

		int errorCode = decodePNG(out, width, height, &(in[0]), in.size(), false);
		if (0 != errorCode)
		{
			fatalError("decodePNG failed with error:" + std::to_string(errorCode));
		}

		//Generate the textures
		glGenTextures(1, &(texture._id));

		glBindTexture(GL_TEXTURE_2D, texture._id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);//0-->unbind the texture

		//give the size of png image
		texture.height = height;//
		texture.width = width;//

		return texture;
	}

}
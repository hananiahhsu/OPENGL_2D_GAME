#pragma once
#include <GL/glew.h>
#include "GLTexture.h"
#include<string>

namespace Gamegine {
	class Sprite
	{
	public:
		Sprite();
		~Sprite();


		void init(float x, float y, float width, float height, std::string texturePath);
		void draw();

	private:
		float _x;
		float _y;
		float _width;
		float _height;
		GLuint _vboID;//32 bit always
		//store textures
		GLTexture _texture;

	};

}
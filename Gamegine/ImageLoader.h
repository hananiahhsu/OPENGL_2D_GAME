#pragma once

#include "GLTexture.h"
#include<string>

namespace Gamegine {
	class ImageLoader
	{
	public:
		//static function-->static function can call only static variable and functions
		//non_static function can call both static and non_static functions and variables
		//Also you should know that static varibale could be valued outside the class but with the scope::
		static	GLTexture loadPNG(const std::string& filePath);


	};

}
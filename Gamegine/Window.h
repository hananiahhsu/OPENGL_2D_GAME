#pragma once

#include<SDL.h>
#include<GL/glew.h>
#include<string>

namespace Gamegine {
	//ENUM CLASS:
	//ENUM maybe similar to enum class,but it's different.
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		//operations of windows
		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
		void swapBuffer();
		int getScreenWidth() { _screenWidth; }
		int getScreenHeight() { _screenHeight; }
	private:
		//handle of the window
		SDL_Window* _sdl_window;
		//parameter of window
		int _screenWidth, _screenHeight;
	};

}
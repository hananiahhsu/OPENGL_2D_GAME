#include "Gamegine.h"
#include<SDL.h>
#include<GL/glew.h>


namespace Gamegine {
	int init()
	{
		//init the system
		SDL_Init(SDL_INIT_EVERYTHING);

		//This function should be put here,if you put it behind glClearColor,it's not proper
		//Brief set an opengl window attribute before creation
		//Here we set a double buffers,so we need to swap the window(eg,A and B windows) in the function of drawGame()
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}

}






#include "Window.h"
#include "Errors.h"

namespace Gamegine {
	Window::Window()
	{
	}


	Window::~Window()
	{
	}



	//operations of windows
	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{

		Uint64 flags = SDL_WINDOW_OPENGL;
		if (currentFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}
		//open an openGL window
		_sdl_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenWidth, flags);

		//important for check
		if (_sdl_window == nullptr)
		{
			fatalError("SDL window couldn't be created.");
		}

		//Set up our OpenGL context
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdl_window);
		if (glContext == nullptr)
		{
			fatalError("SDL_GL Context couldn't be created!");
		}

		//set up our glew(it's optional,but i recommend it)
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			fatalError("Could not initialize glew!");
		}

		//Here it's one way of getting the opengl version,also you could use other third party software(small tool) to get
		//your OpenGL version
		std::printf(".............OpenGL Version:%s.............", glGetString(GL_VERSION));

		//set the background color after each clearing
		glClearColor(1.0f, 0.5f, 1.0f, 0.5f);

		//vertical syncronization()
		//Swap Interval is a means of synchronizing the swapping of the front and back frame buffers with vertical blanks (v-blank): the hardware event where the screen image is updated with data from the front framebuffer . It is a very common means of preventing frame "tearing," (seeing half of one frame and half of another) as often seen in high-motion-content graphics.
		//0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for late swap tearing;
		//vertical retrace:Alternatively referred to as a vertical blanking interval or the vertical sync signal, vertical retrace is a measurement of time related to video displays. It represents the amount of time between the end of one frame being drawn, and the beginning of the next frame.
		SDL_GL_SetSwapInterval(1);

		return 0;
	}



	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(_sdl_window);
	}

}
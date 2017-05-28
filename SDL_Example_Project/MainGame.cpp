#include "MainGame.h"
#include <iostream>
#include <string>
#include <Gamegine/Errors.h>
#include <Gamegine/ImageLoader.h>

MainGame::MainGame():_screenWidth(768),_screenHeight(512),_time(0.0f),_gameState(GameState::PLAY)
                     ,_maxFPS(120.0f)
{

}


MainGame::~MainGame()
{
}



void MainGame::run()
{

	initSystems();
	//Initialzie the sprite
	_sprites.push_back( new Gamegine::Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "E:/X_HSU/OPENGL_2D_GAME/Resources/Textures/cat1.png"); 

	_sprites.push_back(new Gamegine::Sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "E:/X_HSU/OPENGL_2D_GAME/Resources/Textures/cat1.png");


	_sprites.push_back(new Gamegine::Sprite());
	_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "E:/X_HSU/OPENGL_2D_GAME/Resources/Textures/cat1.png");

	_sprites.push_back(new Gamegine::Sprite());
	_sprites.back()->init(0.0f, 0.0f, 1.0f, 1.0f, "E:/X_HSU/OPENGL_2D_GAME/Resources/Textures/cat1.png");



	//load the png into buffer(texture-surface structure,eg glass,steel,wood,paper etc)
	//_playerTexture = ImageLoader::loadPNG("C:/Users/Administrator/Documents/Visual Studio 2015/Projects/SDL_Example_Project1/Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");	 

	gameLoop();
}
void MainGame::initSystems()
{
	/*
	//init the system
	SDL_Init(SDL_INIT_EVERYTHING);

	//This function should be put here,if you put it behind glClearColor,it's not proper
	//Brief set an opengl window attribute before creation
	//Here we set a double buffers,so we need to swap the window(eg,A and B windows) in the function of drawGame()
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	*/
	Gamegine::init();//in Gamegine.cpp


	//The commented lines are moved to window.cpp
/*
	//open an openGL window
	_window = SDL_CreateWindow("Game Engine",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth,_screenHeight,SDL_WINDOW_OPENGL);
	//important for check
	if (_window == nullptr)
	{
		fatalError("SDL window couldn't be created.");
	}

	//Set up our OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
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
	std::printf(".............OpenGL Version:%s.............", glGetString(GGL_STRING));
	
	//set the background color after each clearing
	glClearColor(1.0f,0.5f,1.0f,0.5f);

	//vertical syncronization()
	//Swap Interval is a means of synchronizing the swapping of the front and back frame buffers with vertical blanks (v-blank): the hardware event where the screen image is updated with data from the front framebuffer . It is a very common means of preventing frame "tearing," (seeing half of one frame and half of another) as often seen in high-motion-content graphics.
	//0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for late swap tearing;
	//vertical retrace:Alternatively referred to as a vertical blanking interval or the vertical sync signal, vertical retrace is a measurement of time related to video displays. It represents the amount of time between the end of one frame being drawn, and the beginning of the next frame.
	SDL_GL_SetSwapInterval(1);
*/

	//As you see,the above commented lines have been moved to Window.cpp
	//Init the window(Here you could choose any param from the enum class window:fullscreen,borderless,invisible)
	//here if you set FULLSCREEN,it's not easy to close the window
	_window.create("SDL Game Engine",_screenWidth,_screenHeight,0);//FULLSCREEN

	initShaders(); 


}

//variables in the colorShading.frag
void MainGame::initShaders()
{
	_colorProgram.compileShaders("E:/X_HSU/OPENGL_2D_GAME/ShaderFiles/colorShader.vert","E:/X_HSU/OPENGL_2D_GAME/ShaderFiles/colorShader.frag");
	_colorProgram.addAtrribute("vertexPosition");

	_colorProgram.addAtrribute("vertexColor");

	_colorProgram.addAtrribute("vertexUV");

	_colorProgram.linkerShaders();




}



//game loop
void MainGame::gameLoop()
{
	while (_gameState != GameState::QUIT)
	{
		float startTicks = SDL_GetTicks();
		processInput();

		_time += 0.01;

		//draw the game
		drawGame();
		//Calculate the FPS
		calculateFPS();

		//print only once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (10 == frameCounter)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		//limit the FPS TO the max FPS
		if (1000.0f / _maxFPS > frameTicks)
		{
			SDL_Delay(1000.0f/_maxFPS - frameTicks);
		}
	}
}

//process msg of input
void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		  case SDL_QUIT:
			  _gameState = GameState::QUIT;
			  break;
		  case SDL_MOUSEMOTION:
			  //After output the result of "Used cache texture" Or "Loaded texture",comment the following line,no need
			  //std::cout << event.motion.x << " " << event.motion.y << std::endl;
			  break;
		}
	}
}

//draw the game
void MainGame::drawGame()
{
	//take the variable
	glClearDepth(1.0);//1.0?
	//clear color
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);

	//At the stage of sprite(maybe 2d game),so comment the following codes
/*	//eg.we can draw a triangle on the screen
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex2f(0,0);
	glVertex2f(0, 200);
	glVertex2f(200, 200);
	glEnd();
*/

	_colorProgram.use();

	//bind the textures
	glActiveTexture(GL_TEXTURE0);//GL_TEXTURE1 also okay
	//glBindTexture(GL_TEXTURE_2D,_playerTexture._id);--->change to Sprite.cpp-->draw()

	GLint textureLocation = _colorProgram.getUniformLocation("catSampler");
	glUniform1i(textureLocation,0);//corresponding to GL_TEXTURE0 ABOVE


	//This 2 lines making the effect of wave flowing by the rule  of cosine or sine
	GLuint timeLocation = _colorProgram.getUniformLocation("time");//if the 'uniform float time 'in the colorShading.frag is canceled
	glUniform1f(timeLocation,_time);


	//Use the class sprite to realize some functions
	//_sprite.draw();
	for (int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->draw();
	}

	glBindTexture(GL_TEXTURE_2D,0);

	_colorProgram.unuse();

	//With the presetting of 2 buffers in initSystem(),we need to swap the 2 windows
	//SDL_GL_SwapWindow(_window);
	_window.swapBuffer();
}


//This function is used to calculate the _fps (frame per second)
void MainGame::calculateFPS()
{
	//static -> means 
	static const int NUM_SAMPLES = 10;
	static float frameTime[NUM_SAMPLES];
	static int currentFrame = 0;
	static float prevTicks = SDL_GetTicks();
	float currentTicks;
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTime[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;//assign the value to prevTicks with the value of currentTicks

	int count;

	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}


	float timeTimeAverage = 0;
	for (int i = 0;i < count;i++)
	{
		timeTimeAverage += frameTime[i];
	}
	timeTimeAverage /= count;

	//1s == 1000ms
	if (timeTimeAverage > 0)
	{
		_fps = 1000.0f / timeTimeAverage;
	}
	else
	{
		_fps = 60.0f;
	}

	currentFrame++;
}

















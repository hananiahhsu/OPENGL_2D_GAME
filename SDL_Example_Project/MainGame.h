#pragma once
#include<windows.h>
#include<vector>
#include<SDL/glew.h>
#include<GL/GLU.h>
#include<GL/GL.h>
//#include<GL/freeglut.h>
#include<SDL.h>
#include<SDL_system.h>

#include <Gamegine/Sprite.h>
#include <Gamegine/GLSLProgram.h>
#include <Gamegine/GLTexture.h>
#include <Gamegine/Window.h>
#include "Gamegine/Gamegine.h"
enum class GameState {PLAY,QUIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();


private:
	//we willn't call outside MainGame,so set it as private
	void initSystems();
	//Msg loop
	void gameLoop();
	//process the input massages
	void processInput();
	//
	void drawGame();
	//init shaders
	void initShaders(); 
	//calculate the FPS
	void calculateFPS();
/////////////////////////////////////
//variable
////////////////////////////////////
	//SDL_Window * _window;//After the class of Window is defined,use Window to define _window
	Gamegine::Window _window;

	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	std::vector<Gamegine::Sprite*> _sprites;
	//Sprite _sprite;//commented after above definition

	//GLSL
	Gamegine::GLSLProgram  _colorProgram;

	Gamegine::GLTexture _playerTexture;
	//
	float _time;


	//To get the time of each frame(unit:ms)
	float _fps;
	float _frameTime;
	float _maxFPS;

};


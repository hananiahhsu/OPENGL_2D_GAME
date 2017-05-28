#include<windows.h>
#include<iostream>
#include<SDL.h>
#include<GL/glew.h>
#include "MainGame.h"
int main(int argc,char** argv ) {
	//SDL_Init(SDL_INIT_EVERYTHING);

	MainGame main_game;
	main_game.run();

	//std::cout << "Enter any key to quit...";
	//int a;
	//std::cin >> a;
	return 0;
}
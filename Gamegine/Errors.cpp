
#include "Errors.h"
#include <iostream>
#include<SDL.h>

#include<cstdlib>//???

namespace Gamegine {
	//This function used to check the result of initWindow ?
	void fatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		int temp;
		std::cin >> temp;
		SDL_Quit();//

		exit(69);//
	}

}
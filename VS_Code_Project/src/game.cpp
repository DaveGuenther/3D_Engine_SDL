#include "preprocessor.cpp"
#if defined(PREDEF_PLATFORM_WINDOWS)
	#define SDL_MAIN_HANDLED
	#pragma message("WinMain")
#endif


#include <SDL2/SDL.h>
#include <iostream>



//#if defined(PREDEF_PLATFORM_UNIX)
#include "src/core/Engine_3D.h"
//#endif


int main(int argv, char** args)
{

	std::cout << "Hello World" << std::endl;
	Engine_3D Game_Engine;
	Game_Engine.load_meshes();
 
	while(Game_Engine.is_running()){
		Game_Engine.engine_update();
	}
	
	Game_Engine.shutdown();

	std::cout << "Goodbye" << std::endl;
	return 0;
}
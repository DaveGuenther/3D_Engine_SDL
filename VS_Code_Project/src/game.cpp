#include "preprocessor.cpp"
#if defined(PREDEF_PLATFORM_WINDOWS)
	#define SDL_MAIN_HANDLED
	#pragma message("WinMain")
#endif



#include <SDL2/SDL.h>
#define SDL_STBIMAGE_IMPLEMENTATION // Required for SDL_stbimage.h and bitmap_font.h  Place in main.cpp JUST AFTER #include <SDL2/SDL.h>.  Place the other .h files in other parts of the engine, but not here.
#include <iostream>
#include "core/Engine_3D.h"


//#if defined(PREDEF_PLATFORM_UNIX)

//#endif




int main(int argv, char** args)
{

	
	Engine_3D Game_Engine;
	Game_Engine.load_meshes();
 
	while(Game_Engine.is_running()){
		Game_Engine.engine_update();
	}
	
	Game_Engine.shutdown();
	
	return 0;
}
#include <SDL2/SDL.h>
#include <iostream>
#include "preprocessor.cpp"



//#if defined(PREDEF_PLATFORM_UNIX)
#	include "core/Engine_3D.h"
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
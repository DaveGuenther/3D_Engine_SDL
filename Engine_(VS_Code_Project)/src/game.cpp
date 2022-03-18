
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <unistd.h>

#include <SDL2/SDL.h>

#include "Engine_3D.h"


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
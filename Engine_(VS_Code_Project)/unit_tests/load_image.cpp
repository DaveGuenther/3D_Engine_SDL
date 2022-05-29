#include <iostream>
#include "SDL.h"
//#include "SDL2/SDL_image.h"


int main (int argv, char** args){
    SDL_Window *window;
    SDL_Renderer *renderer;
	window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 380, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
    bool game_is_running=true;
    while(game_is_running){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                game_is_running=false;
            }
        }
    }


    return 0;
}


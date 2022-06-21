#include <iostream>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "utility/PNGTexture.h"



int main (int argv, char** args){
    SDL_Window *window;
    SDL_Renderer *renderer;
	window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 380, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
    
    IMG_Init(IMG_INIT_PNG);

    PNGTexture my_texture("texture.png");

    //SDL_Surface* image = my_texture.getSDL_Surface();

    Uint32 start_array_time, end_array_time, start_surface_time, end_surface_time=0;

    bool game_is_running=true;
    while(game_is_running){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                game_is_running=false;
            }
        }

        
        SDL_Color col;
        SDL_RenderClear(renderer);
        
        start_array_time=SDL_GetTicks();


        for (float v=0;v<=1.0;v+=0.005){
            for (float u=0;u<=1.0;u+=0.005){
                my_texture.getPixelAtUV(u,v,col);
                SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
                SDL_RenderDrawPoint(renderer,u*350,v*350);
            }

        }

        end_array_time=SDL_GetTicks();


        std::cout<< "array Time (ticks): " << end_array_time-start_array_time << "    surface Time (Ticks): " << end_surface_time-start_surface_time << std::endl;

        
        SDL_RenderPresent(renderer);


    }
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}


#include <iostream>
#include "SDL.h"
#include "SDL_image.h"


int main (int argv, char** args){
    SDL_Window *window;
    SDL_Renderer *renderer;
	window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 380, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
    
    IMG_Init(IMG_INIT_PNG);
    	
    // load sample.png into image
    SDL_Surface *image;
    image=IMG_Load("colorgrid.png");
    if(!image) {
        printf("IMG_Load: %s\n", IMG_GetError());
        // handle error
    }

    SDL_Texture* ourPNG=SDL_CreateTextureFromSurface(renderer, image);

    bool game_is_running=true;
    while(game_is_running){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                game_is_running=false;
            }
        }
    
    SDL_SetRenderDrawColor(renderer,0,0,255,255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer,ourPNG, NULL, NULL);

    SDL_RenderPresent(renderer);


    }
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_FreeSurface(image);
    SDL_DestroyTexture(ourPNG);
    SDL_Quit();

    return 0;
}


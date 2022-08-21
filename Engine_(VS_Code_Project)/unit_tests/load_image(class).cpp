#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>
#include <SDL2/SDL.h>
#include "SDL_image.h"
#include "utility/TexturePNG.h"
#include "utility/TextureList.h"

void gfx(SDL_Renderer* renderer){

    
}


int main (int argv, char** args){
    SDL_LogSetAllPriority( SDL_LOG_PRIORITY_WARN );
    SDL_Window *window;
    SDL_Renderer *renderer;
	window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 380, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
    
    TextureList my_list;


    IMG_Init(IMG_INIT_PNG);

    std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
    std::string CWD = std::filesystem::current_path().u8string();
    std::string filename = "texture.png"; 
    my_list.insertOrAssignTexture("determined.png");
    my_list.insertOrAssignTexture("1st_texture.png");
    //my_list.insertOrAssignTexture("1st_texture.png");

    std::shared_ptr<TexturePNG> my_texture = my_list.getTextureByFilename("determined.png");
    std::shared_ptr<TexturePNG> my_texture2 = my_list.getTextureByFilename("1st_texture.png");
    std::shared_ptr<TexturePNG> this_null_ptr = my_list.getTextureByFilename("filenotfound.png");



    Uint32 start_array_time, end_array_time, start_surface_time, end_surface_time=0;

    bool game_is_running=true;
    while(game_is_running){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                game_is_running=false;
            }
        }

        
        SDL_Color col{0,0,0,255};
        SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
        SDL_RenderClear(renderer);
        
        start_array_time=SDL_GetTicks();


        for (float v=0;v<=1.0;v+=0.005){
            for (float u=0;u<=1.0;u+=0.005){
                my_texture->getPixelAtUV(u,v,col);
                SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
                SDL_RenderDrawPoint(renderer,u*350,v*350);
            }

        }

        for (float v=0;v<=1.0;v+=0.005){
            for (float u=0;u<=1.0;u+=0.005){
                my_texture2->getPixelAtUV(u,v,col);
                SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
                SDL_RenderDrawPoint(renderer,u*100,v*100);
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


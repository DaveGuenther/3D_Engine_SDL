#include <SDL2/SDL.h>
#include "Command_Controller.h"
#include <unordered_map>
#include <iostream>
#include <string>


int main (int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Event event;
    SDL_Window *window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    //const Uint8* keystate = SDL_GetKeyboardState(NULL);
    bool is_running = true;
    bool event_polled;
    int x, y, x_old, y_old;
    Uint32 buttons;
    while(is_running){
        
        SDL_PumpEvents();
        x_old = x;
        y_old=y;
        buttons = SDL_GetMouseState(&x, &y);
        if (x_old!=x || y_old!=y) {std::cout << "X: " << x << ", Y: " << y << std::endl;}
        while( SDL_PollEvent( &event ) ){

            switch( event.type ){

                case SDL_KEYDOWN:

                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            std::cout << "Left down" << std::endl;
                            break;
                        case SDLK_RIGHT:
                            std::cout << "Right down" << std::endl;
                            break;
                        case SDLK_UP:
                            std::cout << "Up down" << std::endl;
                            break;
                        case SDLK_DOWN:
                            std::cout << "Down down" << std::endl;
                            break;
                        case SDLK_ESCAPE:
                            std::cout << "ESCAPE down" << std::endl;
                            is_running=false;
                            break;    
                        default:
                            break;

                    }
                    break;

                case SDL_KEYUP:
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:

                            std::cout << "Left UP" << std::endl;
                            break;
                        case SDLK_RIGHT:
                            std::cout << "Right UP" << std::endl;
                            break;
                        case SDLK_UP:
                            std::cout << "Up UP" << std::endl;
                            break;
                        case SDLK_DOWN:
                            std::cout << "Down UP" << std::endl;
                            break;
                        case SDLK_ESCAPE:
                        std::cout << "ESCAPE UP" << std::endl;
                            is_running=true;
                        default:
                            break;
                    }
                    break;
                
                default:
                    break;
            }
        }     
    }

    SDL_Quit();

    return 0;
}
#include <SDL2/SDL.h>
#include "Command_Controller.h"
#include <unordered_map>
#include <iostream>
#include <string>

class Keyboard_Input{

    private:
    SDL_Event event;
    bool is_running;

    public:
    Keyboard_Input(SDL_Event &my_event);
    bool Get_Input();
    void set_is_running(bool running);
    bool get_is_running();


};

Keyboard_Input::Keyboard_Input(SDL_Event &my_event){
    event=my_event;
}

bool Keyboard_Input::Get_Input(){
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
    return is_running;        
}

void Keyboard_Input::set_is_running(bool running){is_running = running;}

bool Keyboard_Input::get_is_running(){ return is_running;}




int main (int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Event event;
    int SCREEN_WIDTH=640;
    int SCREEN_HEIGHT=480;
    SDL_Window *window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    //const Uint8* keystate = SDL_GetKeyboardState(NULL);
    bool is_running = true;
    //bool event_polled;
    int x, y, x_old, y_old;
    Uint32 buttons;
    Keyboard_Input keyboard(event);
    while(is_running){
        
        //mouse stuff
        SDL_PumpEvents();
        x_old = x;
        y_old=y;
        buttons = SDL_GetMouseState(&x, &y);
        if (x_old!=x || y_old!=y) {std::cout << "X: " << float(x-x_old)/(float(SCREEN_WIDTH)/2) << ", Y: " << float(y-y_old)/float(SCREEN_HEIGHT/2) << std::endl;}
        //end mouse stuff
        
        //keyboard stuff
        keyboard.set_is_running(is_running);
        keyboard.Get_Input();
        is_running = keyboard.get_is_running();
        //end keyboard stuff

        /*while( SDL_PollEvent( &event ) ){

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
        } */    
    }

    SDL_Quit();

    return 0;
}
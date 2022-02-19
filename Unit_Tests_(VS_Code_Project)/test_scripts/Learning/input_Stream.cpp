#include <SDL2/SDL.h>
//#include "Command_Controller.h"
#include <unordered_map>
#include <iostream>
#include <string>

enum input_map{PREVIOUS_MAP, CURRENT_MAP};

void print_map(std::unordered_map<int,bool> this_map);

class Keyboard_Scanner{

    private:
    SDL_Event event;
    //bool is_running;
    std::unordered_map<int,bool> curr_key_matrix;
    std::unordered_map<int,bool> prev_key_matrix;

    public:
    Keyboard_Scanner(SDL_Event &my_event);
    void scanInput();
    //void setIsRunning(bool running);
    const std::unordered_map<int,bool>& getMap(input_map this_map);



};

Keyboard_Scanner::Keyboard_Scanner(SDL_Event &my_event){
    event=my_event;
}



void Keyboard_Scanner::scanInput(){
    prev_key_matrix=curr_key_matrix;
    while( SDL_PollEvent( &event ) ){
        
        // This loop will run for each key currently pressed
        switch( event.type ){

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_a){
                    std::cout << "A PRESSED!!" << std::endl;
                }
                //curr_key_matrix.clear();
                curr_key_matrix.insert_or_assign(event.key.keysym.sym,true);
                break;
                /*
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
                */
            case SDL_KEYUP:
                //prev_key_matrix=curr_key_matrix;
                
                curr_key_matrix.erase(event.key.keysym.sym);    
                break;            
            /*
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
            */
            default:
                break;
        }
    } 
    //return is_running;        
}

//void Keyboard_Scanner::setIsRunning(bool running){is_running = running;}

//bool Keyboard_Scanner::getIsRunning(){ return is_running;}

const std::unordered_map<int,bool>& Keyboard_Scanner::getMap(input_map this_map){
    if(this_map==CURRENT_MAP){ return curr_key_matrix;}
    else if(this_map==PREVIOUS_MAP) { return prev_key_matrix;}
    else{ throw std::invalid_argument("Invalid arguement.  Possible values are PREVIOUS_MAP or CURRENT_MAP"); }
}

void print_map(const std::unordered_map<int,bool> this_map){
    for (const std::pair<int,bool> this_item:this_map){
        std::cout << this_item.first << ": " << this_item.second << ", ";
    }
    std::cout << std::endl;
}

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
    Keyboard_Scanner keyboard(event);
    while(is_running){
        
        //mouse stuff
        SDL_PumpEvents();
        x_old = x;
        y_old=y;
        buttons = SDL_GetMouseState(&x, &y);
        if (x_old!=x || y_old!=y) {std::cout << "X: " << float(x-x_old)/(float(SCREEN_WIDTH)/2) << ", Y: " << float(y-y_old)/float(SCREEN_HEIGHT/2) << std::endl;}
        //end mouse stuff
        
        //keyboard stuff
        //keyboard.setIsRunning(is_running);
        keyboard.scanInput();
        if (keyboard.getMap(PREVIOUS_MAP)!=keyboard.getMap(CURRENT_MAP)){
            std::cout << "Prev: ";
            print_map(keyboard.getMap(PREVIOUS_MAP));
            std::cout << "Curr: ";
            print_map(keyboard.getMap(CURRENT_MAP));
        }
        //is_running = keyboard.getIsRunning();
        //end keyboard stuff

    }

    SDL_Quit();

    return 0;
}
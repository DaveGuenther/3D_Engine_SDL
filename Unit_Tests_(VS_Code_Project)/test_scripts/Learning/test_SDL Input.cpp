#include <SDL2/SDL.h>

#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>



int main (int argc, char *argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Event event;
    SDL_Window *window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    

    std::unordered_map<int, std::string> key_binding_map;
    key_binding_map.insert_or_assign(SDLK_UP,"Forward");
    key_binding_map.insert_or_assign(SDLK_DOWN,"Backward");
    key_binding_map.insert_or_assign(SDLK_LEFT,"Left");
    key_binding_map.insert_or_assign(SDLK_RIGHT,"Right");
    
    
    std::vector<std::vector<std::string>> current_commands(2);
    std::vector<std::vector<std::string>> prev_commands(2);
    //command_map.insert_or_assign("Forward",false);
    //command_map.insert_or_assign("Backward",false);
    //command_map.insert_or_assign("Left",false);
    //command_map.insert_or_assign("Right",false);

    
    
    // Declare an iterator to unordered_map
    std::unordered_map<int, std::string>::iterator it;


    //for (auto x : key_binding_map)
    //  std::cout << x.first << " " << x.second << std::endl;


    bool is_running = true;
    bool event_polled;
    int x, y, x_old, y_old;
    Uint32 buttons;
    while(is_running){
            for (auto this_cmd: current_commands[1]){ std::cout << this_cmd << std::endl;}
                prev_commands[0]=current_commands[0];
                prev_commands[1]=current_commands[1];
                current_commands[0].clear();
                current_commands[1].clear();           
        SDL_PumpEvents();
        x_old = x;
        y_old=y;
        std::string my_vector, my_vector_old;
        buttons = SDL_GetMouseState(&x, &y);
        if (x_old!=x || y_old!=y) {std::cout << "X: " << x << ", Y: " << y << std::endl;}
        while( SDL_PollEvent( &event ) ){
         
            /*my_vector_old = my_vector;
            my_vector= "[";
            for (auto this_command:command_map){
                my_vector += std::to_string(this_command.second);
                my_vector += ", ";
            }
            my_vector += "]";
            if (my_vector_old != my_vector) {std::cout << my_vector << std::endl;}*/
            switch( event.type ){

                case SDL_KEYDOWN:   
                    // search hash map to see if any of the possible key bindings include event.key.keysym.sym
                    it = key_binding_map.find(event.key.keysym.sym);
                    if (it != key_binding_map.end()){
                        // If the key is pressed, associate it's binding to the command vector
                        //std::cout << it->second << " Pressed" << std::endl;
                        current_commands[1].push_back(it->second);
                    }
                    break;
                
                case SDL_KEYUP:   
                    // search hash map to see if any of the possible key bindings include event.key.keysym.sym
                    it = key_binding_map.find(event.key.keysym.sym);
                    if (it != key_binding_map.end()){
                        // If the key is pressed, associate it's binding to the command vector
                        //std::cout << it->second << " Released" << std::endl;
                        current_commands[0].push_back(it->second);
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
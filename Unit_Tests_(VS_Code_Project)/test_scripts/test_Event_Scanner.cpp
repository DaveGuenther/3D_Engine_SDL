#include <SDL2/SDL.h>
#include "Event_Scanner.h"
#include <iostream>

void print_map(std::unordered_map<int,bool> this_map);

void print_map(const std::unordered_map<int,bool> this_map){
    for (const std::pair<int,bool> this_item:this_map){
        std::cout << this_item.first << ": " << this_item.second << ", ";
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Event event;
    Renderer Engine_Renderer;


    bool is_running = true;
    Event_Scanner input_events(event, Engine_Renderer );
    while (is_running){
        input_events.scanInput();
        if (input_events.getMap(PREVIOUS_MAP)!=input_events.getMap(CURRENT_MAP)){
            std::unordered_map<int, bool> this_map = input_events.getMap(CURRENT_MAP);
            if (this_map.find(SDLK_ESCAPE)!=this_map.end()){ is_running=false; }

            std::cout << "Prev: ";
            print_map(input_events.getMap(PREVIOUS_MAP));
            std::cout << "Curr: ";
            print_map(input_events.getMap(CURRENT_MAP));
        }
    }
    return 0;
}
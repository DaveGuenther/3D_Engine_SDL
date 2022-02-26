#ifndef EVENT_SCANNER_H
#define EVENT_SCANNER_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include "Renderer.h"

enum input_map{PREVIOUS_MAP, CURRENT_MAP};

class Event_Scanner{

    private:
    SDL_Event event;

    std::unordered_map<Uint32,bool> curr_key_matrix;
    std::unordered_map<Uint32,bool> prev_key_matrix;

    int curr_mouse_x, curr_mouse_y, prev_mouse_x, prev_mouse_y, delta_mouse_x, delta_mouse_y;

    int SCREEN_W, SCREEN_H;

    //void screenToCart()



    public:
    Event_Scanner();
    Event_Scanner(SDL_Event &my_event, Renderer &my_renderer);
    void scanInput();
    //void setIsRunning(bool running);
    const std::unordered_map<Uint32,bool>& getMap(input_map this_map);



   

};


#endif
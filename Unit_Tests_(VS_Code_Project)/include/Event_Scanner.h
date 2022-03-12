#ifndef EVENT_SCANNER_H
#define EVENT_SCANNER_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include "Renderer.h"

enum input_map{PREVIOUS_MAP, CURRENT_MAP, MOUSE_BUTTON_MAP};

class Event_Scanner{

    private:
    SDL_Event event;

    std::unordered_map<std::string,bool> curr_key_matrix;
    std::unordered_map<std::string, bool> prev_key_matrix;

    std::unordered_map<std::string, bool> mouse_button_matrix;


    std::unordered_map<std::string, float> curr_range_input_matrix;
    std::unordered_map<std::string, float> prev_range_input_matrix;

    float curr_mouse_x, curr_mouse_y, prev_mouse_x, prev_mouse_y, delta_mouse_x, delta_mouse_y;

    int SCREEN_W, SCREEN_H;

    //void screenToCart()



    public:
    Event_Scanner();
    Event_Scanner(SDL_Event &my_event, Renderer &my_renderer);
    void scanInput();
    //void setIsRunning(bool running);
    const std::unordered_map<std::string,bool>& getTactileMap(input_map this_map);
    const std::unordered_map<std::string,float>& getRangeMap(input_map this_map);
    



   

};


#endif
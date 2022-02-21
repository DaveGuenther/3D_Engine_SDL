#include "Event_Scanner.h"
#include "Renderer.h"

Event_Scanner::Event_Scanner(SDL_Event &my_event, Renderer &my_renderer){
    event=my_event;
    curr_mouse_x=0;
    curr_mouse_y=0;
    prev_mouse_x=0;
    delta_mouse_x=0;
    delta_mouse_y=0;
    SCREEN_H=my_renderer.getWindow_Height();
    SCREEN_W=my_renderer.getWindow_Width();
}

void Event_Scanner::scanInput(){
    prev_key_matrix=curr_key_matrix;
    while( SDL_PollEvent( &event ) ){
        
        // This loop will run for each key currently pressed
        switch( event.type ){

            case SDL_KEYDOWN:
                //curr_key_matrix.clear();
                curr_key_matrix.insert_or_assign(event.key.keysym.sym,true);
                break;

            case SDL_KEYUP:
                //prev_key_matrix=curr_key_matrix;
                
                curr_key_matrix.erase(event.key.keysym.sym);   
                break;

            case SDL_MOUSEMOTION:
                prev_mouse_x=curr_mouse_x;
                prev_mouse_y=curr_mouse_y;
                curr_mouse_x=(event.motion.x-(SCREEN_W/2))/(SCREEN_W/2);
                curr_mouse_y=(event.motion.y-(SCREEN_H/2))/(SCREEN_H/2);
                delta_mouse_x = curr_mouse_x-prev_mouse_x;
                delta_mouse_y = curr_mouse_y-prev_mouse_y;

                break;

            case SDL_MOUSEBUTTONDOWN:
                break;

            case SDL_MOUSEBUTTONUP:
                break; 

            default:
                break;
        }
    }       
}

const std::unordered_map<Uint32,bool>& Event_Scanner::getMap(input_map this_map){
    if(this_map==CURRENT_MAP){ return curr_key_matrix;}
    else if(this_map==PREVIOUS_MAP) { return prev_key_matrix;}
    else{ throw std::invalid_argument("Invalid arguement.  Possible values are PREVIOUS_MAP or CURRENT_MAP"); }
}
#include <memory>
#include "Event_Scanner.h"
#include "../render/Renderer.h"

Event_Scanner::Event_Scanner(GameStateSubject &subject, SDL_Event &my_event, std::shared_ptr<Renderer> my_renderer):game_state_subject(subject){
    
    this->Engine_State=new Game_Engine_State_Observer(game_state_subject);
    event=my_event;
    curr_mouse_x=0;
    curr_mouse_y=0;
    prev_mouse_x=0;
    delta_mouse_x=0;
    delta_mouse_y=0;
    SCREEN_H=my_renderer->getWindowHeight();
    SCREEN_W=my_renderer->getWindowWidth();
    this->my_renderer = my_renderer;
    SDL_PollEvent( &event );
    //my_renderer->resetMouseXY();
    //captureMouseMovement(); // Has to be called once to handle mouse locking to center of screen without forcing a huge rotation action.
    prev_range_input_matrix=curr_range_input_matrix;

}

void Event_Scanner::captureMouseMovement(){
    prev_mouse_x=curr_mouse_x;
    prev_mouse_y=curr_mouse_y;
    curr_mouse_x=(float(event.motion.x)-(float(SCREEN_W)/2))/(float(SCREEN_W)/2);
    curr_mouse_y=-(float(event.motion.y)-(float(SCREEN_H)/2))/(float(SCREEN_H)/2);
    if (curr_mouse_x!=0.0f) {delta_mouse_x = curr_mouse_x-prev_mouse_x;} else {delta_mouse_x=0.0f;}
    if (curr_mouse_y!=0.0f) {delta_mouse_y = curr_mouse_y-prev_mouse_y;} else {delta_mouse_y=0.0f;}

    curr_range_input_matrix.insert_or_assign("MOUSE_X",event.motion.x);
    curr_range_input_matrix.insert_or_assign("MOUSE_Y",event.motion.y);

    curr_range_input_matrix.insert_or_assign("MOUSE_X_DELTA",delta_mouse_x);
    curr_range_input_matrix.insert_or_assign("MOUSE_Y_DELTA",delta_mouse_y);   
}

void Event_Scanner::scanInput(){
    //my_renderer->resetMouseXY();     
    prev_key_matrix=curr_key_matrix;
    prev_range_input_matrix=curr_range_input_matrix;
    //if (this->Engine_State->getGameState()==CONSOLE) {
    //    SDL_StartTextInput();
    //}
    //if (!prev_key_matrix.empty() && !curr_key_matrix.empty()) { prev_key_matrix=curr_key_matrix; }
    while( SDL_PollEvent( &event ) ){
        
        // This loop will run for each key currently pressed
        switch( event.type ){

            case SDL_KEYDOWN:
                //curr_key_matrix.clear();
                curr_key_matrix.insert_or_assign("KEY:"+std::to_string(event.key.keysym.sym),true);
                break;

            case SDL_KEYUP:
                //prev_key_matrix=curr_key_matrix;
                
                curr_key_matrix.erase("KEY:"+std::to_string(event.key.keysym.sym));   
                break;

            case SDL_MOUSEMOTION:
                //captureMouseMovement();
                break;

            case SDL_MOUSEBUTTONDOWN:{
                //int button_value=0;
                //button_value= event.button.button;
                //curr_key_matrix.insert_or_assign("MOUSE:"+std::to_string(event.button.button), true);
                
                break;
            }
            case SDL_MOUSEBUTTONUP:
               //curr_key_matrix.erase("MOUSE:"+std::to_string(event.button.button));
                break; 

            case SDL_TEXTINPUT:
                this->current_string.append(event.text.text);
                std::cout << current_string << std::endl;
                break;

            default:
                break;
        }

    }    
     
}

const std::unordered_map<std::string,bool>& Event_Scanner::getTactileMap(input_map this_map){

    if(this_map==CURRENT_MAP){ return curr_key_matrix;}
    else if(this_map==PREVIOUS_MAP) { return prev_key_matrix;}
    else if(this_map==MOUSE_BUTTON_MAP) { return mouse_button_matrix; }
    else{ throw std::invalid_argument("Invalid arguement.  Possible values are PREVIOUS_MAP, CURRENT_MAP, or MOUSE_BUTTON_MAP"); }
}

const std::unordered_map<std::string,float>& Event_Scanner::getRangeMap(input_map this_map){
    if(this_map==CURRENT_MAP){ return curr_range_input_matrix;}
    else if(this_map==PREVIOUS_MAP) { return prev_range_input_matrix;}
    else{ throw std::invalid_argument("Invalid arguement.  Possible values are PREVIOUS_MAP, CURRENT_MAP"); }
}
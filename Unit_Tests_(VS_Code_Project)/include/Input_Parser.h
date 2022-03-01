#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <SDL2/SDL.h>
#include "Gamestate_Observer_Pattern.h"
#include "Event_Scanner.h"
#include "KeyBindings.h"


class Input_Parser{
    private:
        SDL_Event event;
        Game_Engine_State_Observer* Engine_State;
        Bindings bindings;
        Event_Scanner* input_events =NULL;
        GameStateSubject &game_state_subject;
        void print_map(const std::unordered_map<std::string,bool> this_map);

    public: 
        Input_Parser(GameStateSubject &subject, Renderer &my_renderer, std::string binding_filename);
        ~Input_Parser();
        void scanInput();

};


#endif
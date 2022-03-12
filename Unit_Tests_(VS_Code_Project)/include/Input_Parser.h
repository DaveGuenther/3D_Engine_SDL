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
        std::unordered_map<std::string,bool> curr_commands;
        std::unordered_map<std::string,float> curr_range_input;
        std::unordered_map<std::string,bool> prev_commands;

    public: 
        Input_Parser(GameStateSubject &subject, Renderer &my_renderer, std::string binding_filename);
        const std::unordered_map<std::string,bool> getCurrentCommands();
        const std::unordered_map<std::string,float> getRangeInput();
        ~Input_Parser();
        void scanInput();

};


#endif
#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

//#include <memory>
#include <memory>
#include <SDL2/SDL.h>
#include "core/Gamestate_Observer_Pattern.h"
#include "input/Event_Scanner.h"
#include "input/KeyBindings.h"


class Input_Parser{
    private:
        SDL_Event event;
        Game_Engine_State_Observer* Engine_State;
        Bindings bindings;
        Event_Scanner* input_events =NULL;
        GameStateSubject &game_state_subject;
        std::unordered_map<std::string,bool> curr_commands;
        std::unordered_map<std::string,float> curr_range_input;
        std::unordered_map<std::string,bool> prev_commands;
        bool rangeInputChanged;
        
        /**
         * @brief This function is not actively used.  It prints out the state of the command map
         * 
         * @param this_map 
         */
        void print_map(const std::unordered_map<std::string,bool> this_map);
        
    public: 
        Input_Parser(GameStateSubject &subject, std::shared_ptr<Renderer> my_renderer, std::string binding_filename);
        
        /**
         * @brief Get the Current Commands object
         * 
         * @return const std::unordered_map<std::string,bool> 
         */
        const std::unordered_map<std::string,bool> getCurrentCommands();
        
        /**
         * @brief Get the Range Input object
         * 
         * @return const std::unordered_map<std::string,float> 
         */
        const std::unordered_map<std::string,float> getRangeInput();
        
        /**
         * @brief This function checks to see if the Range Input has changed since the last frame.  Returns true if it has and false if it has not.
         * 
         * @return true 
         * @return false 
         */
        const bool didRangeInputChange();
        ~Input_Parser();
        
        /**
         * @brief This function interfaces with the Event_Scanner instance to capture both the current and previous keyboard input and range input vectors.
         * 
         */
        void scanInput();

};


#endif
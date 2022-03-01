#include "Input_Parser.h"

Input_Parser::Input_Parser(GameStateSubject &subject, Renderer &my_renderer, std::string binding_filename) :game_state_subject(subject){
    this->Engine_State=new Game_Engine_State_Observer(game_state_subject);
    bindings.loadBinding(binding_filename);
    //bindings.loadBinding("in_game_bindings.cfg");
    input_events = new Event_Scanner(event, my_renderer );



}


Input_Parser::~Input_Parser(void){

    delete input_events;
    delete Engine_State;
    
}

void Input_Parser::scanInput(){

    input_events->scanInput();
    if (input_events->getMap(PREVIOUS_MAP)!=input_events->getMap(CURRENT_MAP)){
        std::unordered_map<Uint32, bool> curr_key_map = input_events->getMap(CURRENT_MAP);
        std::unordered_map<Uint32, bool> prev_key_map = input_events->getMap(PREVIOUS_MAP);
        std::unordered_map<std::string, bool> curr_command_map = bindings.getCommandMapFromKeycodes(curr_key_map);
        std::unordered_map<std::string, bool> prev_command_map = bindings.getCommandMapFromKeycodes(prev_key_map);

        if (curr_key_map.find(SDLK_ESCAPE)!=curr_key_map.end()){ game_state_subject.setState(QUIT); }

        std::cout << "Prev: ";
        print_map(prev_command_map);
        std::cout << "Curr: ";
        print_map(curr_command_map);
    }
}

void Input_Parser::print_map(const std::unordered_map<std::string,bool> this_map){
    for (const std::pair<std::string,bool> this_item:this_map){
        std::cout << this_item.first << ": " << this_item.second << ", ";
    }
    std::cout << std::endl;
}
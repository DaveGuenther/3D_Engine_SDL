#include <SDL2/SDL.h>
#include "Event_Scanner.h"
#include "KeyBindings.h"
#include "GameState_Observer_Pattern.h"
#include <iostream>



class Game_Engine{
    private:
        Renderer Engine_Renderer;
        bool isRunning; //If set to false, this will end the 3D engine during the next engine_update()
        SDL_Event event;
        Mesh_Pipeline mesh_pipeline; // contains all of the objects that the engine will need to render
        //Triangle_Modifications_Pipeline tri_modifications;
        
        GameStateSubject game_state_subject;
        Game_Engine_State_Observer* Engine_State;
        float fTheta, tTheta;
        Bindings in_world_bindings;
        Event_Scanner* input_events =NULL;
        void print_map(const std::unordered_map<std::string,bool> this_map);
        
        
    public:
        Game_Engine();
        ~Game_Engine(void);
        /**
         * @brief This Getter method tells the main game loop the status of the engine, it should be used to terminate the game loop in main()
         * 
         */
        bool is_running();
        /**
         * @brief This method is called once during the game loop.  It queries for input, requests mesh rotations and translations, and projects the new frame on the screen.
         * 
         */
        void engine_update();

        /**
         * @brief Used to shutdown the SDL systems.
         * 
         */
        void shutdown();

};

Game_Engine::Game_Engine(){

    SDL_Init(SDL_INIT_EVERYTHING);
    isRunning = true;
    fTheta=50.0f;
    tTheta=45.0f;
    //this->game_state_subject = new GameStateSubject;
    this->Engine_State=new Game_Engine_State_Observer(game_state_subject);
    //this->my_subject.addSubscriber(this);
    game_state_subject.setState(MENU);
    in_world_bindings.loadBinding("config.cfg");

    input_events = new Event_Scanner(event, Engine_Renderer );
    game_state_subject.setState(IN_WORLD);

}

Game_Engine::~Game_Engine(void){

    delete input_events;
    
}

bool Game_Engine::is_running(){
    return isRunning;
}

void Game_Engine::engine_update(){
    
    input_events->scanInput();
    switch (this->game_state_subject.getState()){
        case IN_WORLD:
            if (input_events->getMap(PREVIOUS_MAP)!=input_events->getMap(CURRENT_MAP)){
                std::unordered_map<Uint32, bool> curr_key_map = input_events->getMap(CURRENT_MAP);
                std::unordered_map<Uint32, bool> prev_key_map = input_events->getMap(PREVIOUS_MAP);
                std::unordered_map<std::string, bool> curr_command_map = in_world_bindings.getCommandMapFromKeycodes(curr_key_map);
                std::unordered_map<std::string, bool> prev_command_map = in_world_bindings.getCommandMapFromKeycodes(prev_key_map);

                if (curr_key_map.find(SDLK_ESCAPE)!=curr_key_map.end()){ isRunning=false; }

                std::cout << "Prev: ";
                print_map(prev_command_map);
                std::cout << "Curr: ";
                print_map(curr_command_map);
            }
            break;
        default:
            if (input_events->getMap(PREVIOUS_MAP)!=input_events->getMap(CURRENT_MAP)){
                std::unordered_map<Uint32, bool> this_map = input_events->getMap(CURRENT_MAP);
                if (this_map.find(SDLK_ESCAPE)!=this_map.end()){ isRunning=false; }
            break;
            }
    }

}

void Game_Engine::shutdown(){
    SDL_Quit();

}

void Game_Engine::print_map(const std::unordered_map<std::string,bool> this_map){
    for (const std::pair<std::string,bool> this_item:this_map){
        std::cout << this_item.first << ": " << this_item.second << ", ";
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]){
    

    Game_Engine game_engine;

	while(game_engine.is_running()){
		game_engine.engine_update();
	}
	
	game_engine.shutdown();

    return 0;
}
#include <SDL2/SDL.h>
#include "input/Event_Scanner.h"
#include "input/KeyBindings.h"
#include "GameState_Observer_Pattern.h"
#include "input/Input_Parser.h"
#include <iostream>
#include <unordered_map>
#include "Frame_Rate_Manager.h"


class Game_Engine{
    private:
        Renderer Engine_Renderer;
        bool isRunning; //If set to false, this will end the 3D engine during the next engine_update()
        
        Mesh_Pipeline mesh_pipeline; // contains all of the objects that the engine will need to render
        //Triangle_Modifications_Pipeline tri_modifications;
        
        GameStateSubject game_state_subject;
        Game_Engine_State_Observer* Engine_State;
        float fTheta, tTheta;
        Input_Parser* MENU_Input_Parser;
        Input_Parser* INWORLD_Input_Parser; 
        
        

        
        
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
    this->MENU_Input_Parser = new Input_Parser(game_state_subject, Engine_Renderer, "menu_bindings.cfg");
    this->INWORLD_Input_Parser = new Input_Parser(game_state_subject, Engine_Renderer, "in_game_bindings.cfg");
    game_state_subject.setState(MENU);
    game_state_subject.setState(IN_WORLD);
    

    
    //game_state_subject.setState(IN_WORLD);

}

Game_Engine::~Game_Engine(void){


    
}

bool Game_Engine::is_running(){
    return isRunning;
}

void Game_Engine::engine_update(){
    
    //input_events->scanInput();
    switch (this->game_state_subject.getState()){
        case QUIT:
            isRunning=false;
            break;
        case IN_WORLD:{
            INWORLD_Input_Parser->scanInput();
            std::unordered_map<std::string,bool> my_commands= INWORLD_Input_Parser->getCurrentCommands();
            //for (auto comm:my_commands){
            //    std::cout << comm.first << ":" << comm.second << "    ";
            //}
            //std::cout << std::endl;
            break;
        }
        case MENU:
            MENU_Input_Parser->scanInput();
            break;
        default:
            break;
    }

}

void Game_Engine::shutdown(){
    SDL_Quit();

}


int main(int argc, char *argv[]){
    

    Game_Engine game_engine;

	while(game_engine.is_running()){
		game_engine.engine_update();
	}
	
	game_engine.shutdown();

    return 0;
}
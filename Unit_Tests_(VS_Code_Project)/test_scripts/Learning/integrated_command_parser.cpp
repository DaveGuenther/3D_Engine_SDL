#include <SDL2/SDL.h>
#include "Event_Scanner.h"
#include "KeyBindings.h"
#include "GameState_Observer_Pattern.h"
#include "Input_Parser.h"
#include <iostream>
#include <unordered_map>
#include "Frame_Rate_Manager.h"

enum ActionCommandState {OFF, TRIG_ATTACK, ATTACK, SUSTAIN, TRIG_RELEASE, RELEASE};

class ICommand{
    public:
        void trigger();
        virtual void update(bool key_pressed)=0;
        const bool isComplete();
        const bool isRunning();
        const bool isReadyToDestroy();
        const std::string getName();
    protected: 
        bool is_running;
        bool is_key_pressed;
        std::string command_name;
        bool readyToDestroy;
        std::string name;
};

const bool ICommand::isRunning(){ return this->is_running; }

const std::string ICommand::getName() { return this->name; }

const bool ICommand::isReadyToDestroy(){ return this->readyToDestroy; }

void ICommand::trigger(){ 
    this->is_key_pressed=true;
    this->is_running=true; 
}


class TwoAxisRangeCommand:public ICommand{
    private:
        float x_range;
        float y_range;
        

    public:
        TwoAxisRangeCommand(std::string command_name, float x_range, float y_range);
        void update(bool key_pressed);

};

TwoAxisRangeCommand::TwoAxisRangeCommand(std::string command_name, float x_range, float y_range):x_range(x_range),y_range(y_range){    
    is_running=true;
}


void TwoAxisRangeCommand::update(bool key_pressed){
    if (is_running){
        std::cout<< "  Applying TwoAxisMovement X: " << x_range << " Y: " << y_range;
        this->is_running=false;
    }
    //this->is_running=false;
    this->readyToDestroy=true;
}



class WalkCommand:public ICommand{
    private:

        float attack_speed_delta, release_speed_delta;
        float speed; // 0.0-1.0  0.0 is stopped, 1.0 is full speed
        float max_speed; // m/s
        float FPS;
        ActionCommandState action_state;
        void setActionState();
        

    public:
        WalkCommand(std::string command_name, float attack, float release, float max_speed, float FPS);
        void setAttack(float attack);
        void setRelease(float release);
        void update(bool key_pressed);

};



WalkCommand::WalkCommand(std::string command_name, float attack, float release, float max_speed, float FPS){
    this->speed=0;
    this->is_running=false;
    this->FPS=FPS;
    this->max_speed = max_speed;
    this->attack_speed_delta = (attack * FPS)/max_speed;
    this->release_speed_delta = (release * FPS)/max_speed;
    this->speed;
    this->is_key_pressed=false;
    this->action_state=OFF;
    this->max_speed=max_speed;
    this->command_name = command_name;
    this->readyToDestroy=false;

}

void WalkCommand::setActionState(){
    
    switch (action_state)
    {
    case OFF:{
        if (is_key_pressed) { action_state=TRIG_ATTACK; }
        break;
    }
    case TRIG_ATTACK:{
        is_running = true;
        action_state = ATTACK;
        break;
    }
    case ATTACK:{
        if(is_key_pressed){
            if (speed>=max_speed) { action_state=SUSTAIN; }
        }else{ 
            is_key_pressed=false;
            action_state = TRIG_RELEASE; 
        }
        break;
    }
    case SUSTAIN:{
        if(!is_key_pressed) { 
            is_key_pressed=false;
            action_state = TRIG_RELEASE; 
        }
        break;
    }
    case TRIG_RELEASE:{
        action_state=RELEASE;
        break;
    }
    case RELEASE:{
        if (is_key_pressed){ action_state=TRIG_ATTACK; }
        else{
            if(speed<=0){ action_state=OFF; }
            else { action_state=RELEASE; }
        }
        break;
    }
    default:
        break;
    }
}

void WalkCommand::setAttack(float attack){ this->attack_speed_delta = (attack * FPS)/max_speed; }

void WalkCommand::setRelease(float release){ this->release_speed_delta = (release * FPS)/max_speed; }
  
    
void WalkCommand::update(bool key_pressed){
    this->is_key_pressed=key_pressed;
    setActionState();
    switch (action_state)
    {
    case OFF:{
        is_running=false;
        speed=0;
        break;
    }
    case TRIG_ATTACK:{
        is_running=true;
        break;
    }
    case ATTACK:{
        speed+=attack_speed_delta;
        break;
    }
    case SUSTAIN:{
        speed=speed;
        break;
    }
    case TRIG_RELEASE:
        //Place Holder
        break;
    case RELEASE:{
        speed-=release_speed_delta;
        break;
    }
    default:
        break;
    }

    // use speed to update meshes here

    std::cout << "    " << command_name << ": " << this->speed;
}

//bool WalkCommand::isComplete(){ return this->is_command_complete; }


/**
 * @brief Gets the number of Commands that are being processed in the map
 * 
 * @param command_map 
 * @return int 
 */
int numberOfActiveCommands(std::unordered_map<std::string, ICommand*> &command_map){
    int number_of_active_actions=0;
    std::unordered_map<std::string, ICommand*>::iterator it = command_map.begin();
    while (it!=command_map.end()){
        if (it->second->isRunning()) { number_of_active_actions+=1; }
        it++;
    }
    return number_of_active_actions;
}

/*std::unordered_map<std::string,bool> updateInput(){
    
    return command_map;
}*/


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
        float FPS;
        Frame_Rate_Manager* VariableFrameRate; 
        std::unordered_map<std::string, ICommand*> command_map;

        
        
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
    this->FPS=60;
    this->VariableFrameRate = new Frame_Rate_Manager(FPS);
    
    command_map.insert_or_assign("MOVE_FORWARD", new WalkCommand("MOVE_FORWARD", 0.5f, 0.5f, 20.0f, FPS));
    command_map.insert_or_assign("MOVE_BACKWARD", new WalkCommand("MOVE_BACKWARD",0.5f, 0.5f, 20.0f, FPS));
    command_map.insert_or_assign("STRAFE_LEFT", new WalkCommand("STRAFE_LEFT",0.5f, 0.5f, 20.0f, FPS));
    command_map.insert_or_assign("STRAFE_RIGHT", new WalkCommand("STRAFE_RIGHT",0.5f, 0.5f, 20.0f, FPS));
    
    
    game_state_subject.setState(IN_WORLD);

}

Game_Engine::~Game_Engine(void){


    
}

bool Game_Engine::is_running(){
    return isRunning;
}

void Game_Engine::engine_update(){
    VariableFrameRate->setFrameStart();
    //input_events->scanInput();
    switch (this->game_state_subject.getState()){
        case QUIT:
            isRunning=false;
            break;
        case IN_WORLD:{
            INWORLD_Input_Parser->scanInput();
            std::unordered_map<std::string,bool> input_tactile_map = INWORLD_Input_Parser->getCurrentCommands();
            std::unordered_map<std::string,float> input_range_map = INWORLD_Input_Parser->getRangeInput();
            
            //  Translate parsed input to input commands
            for (auto input:input_tactile_map){ command_map.at(input.first)->trigger(); } // Tactile Input
            float range_x, range_y;
            for (auto range_input:input_range_map) {  
                if (range_input.first.find("MOUSE_X_DELTA") != std::string::npos){ range_x=range_input.second; }
                if (range_input.first.find("MOUSE_Y_DELTA") != std::string::npos){ range_y=range_input.second; }
            }
            command_map.insert_or_assign("LOOK_XY", new TwoAxisRangeCommand("LOOK_XY", range_x, range_y));

            // for each active command, update the command's action loop
            int num_commands_active = numberOfActiveCommands(command_map);
            if (num_commands_active>0){
                std::vector<std::string> destroyable_commands;
                for (auto command:command_map){
                    if (command.second->isRunning()) { 
                        // Find a way to look through input_map.first to find out if command.first is MISSING from it  If so, command.second->release().  
                        // Then update.  It's the only way to identify that a key release occurred
                        std::string command_to_find = command.first;
                        if (input_tactile_map.find(command_to_find) != input_tactile_map.end()) { 
                            // Key for command is still pressed
                            command.second->update(true);  
                        } else { 
                            // key for command is no longer pressed
                            command.second->update(false); 
                        }                        
                    }
                    if (command.second->isReadyToDestroy()) { 
                        destroyable_commands.push_back(command.second->getName()); 
                    }
                    
                }
                std::cout << std::endl;
                // clean up command_map and destroy completed objects;
                for (auto this_command_name:destroyable_commands){
                    command_map.erase(this_command_name);
                }           
                
            }



            break;
        }
        case MENU:{
            MENU_Input_Parser->scanInput();
            break;
        }
        default:
            break;
    }
    VariableFrameRate->setFrameEnd();
    VariableFrameRate->delay();
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
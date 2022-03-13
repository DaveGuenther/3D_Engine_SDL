#include <SDL2/SDL.h>
#include <iostream>
#include <unordered_map>
#include "Frame_Rate_Manager.h"

enum ActionCommandState {ATTACK, RELEASE};

class ICommand{
    public:
        void trigger();
        virtual void update(bool key_pressed)=0;
        const bool isComplete();
        const bool isRunning();
    protected: 
        bool is_command_complete;
        bool is_running;
        
};

const bool ICommand::isComplete(){ return this->is_command_complete; }

const bool ICommand::isRunning(){ return this->is_running; }

void ICommand::trigger(){ is_running=true; }

class TwoAxisRangeCommand:public ICommand{
    private:
        float x_range;
        float y_range;
        bool is_command_complete;

    public:
        TwoAxisRangeCommand(float x_range, float y_range);
        void update(bool key_pressed);

};

TwoAxisRangeCommand::TwoAxisRangeCommand(float x_range, float y_range):x_range(x_range),y_range(y_range){
    is_command_complete=false;    
    is_running=false;
}



void TwoAxisRangeCommand::update(bool key_pressed){
    this->is_running=true;
    if (!is_command_complete){
        std::cout<< "Applying TwoAxisMovement X: " << x_range << "   Y: " << y_range << std::endl;
        this->is_command_complete=true;
    }
    this->is_running=false;
}



class WalkCommand:public ICommand{
    private:
        float attack_end_timestamp; // timestamp in milliseconds
        float release_end_timestamp; // timestamp in milliseconds
        float release_seconds;
        float speed; // 0.0-1.0  0.0 is stopped, 1.0 is full speed
        float max_speed; // m/s
        bool is_action_attack;
        float FPS;

        Uint64 start_timestamp;
        Uint64 current_time;
    public:
        WalkCommand(float attack, float release, float FPS);
        void setAttack(float attack);
        void setRelease(float release);
        void update(bool key_pressed);
};

WalkCommand::WalkCommand(float attack, float release, float FPS){
    this->speed=0;
    this->is_command_complete=false;
    this->FPS=FPS;
    this->start_timestamp = 0;
    this->attack_end_timestamp = start_timestamp + (attack*FPS);
    this->release_seconds = release;
    this->is_action_attack=true;  // This is set to true by default and it used as a momentary switch once the Release state is triggered.
    this->current_time=start_timestamp;

}

void WalkCommand::setAttack(float attack){ this->attack_end_timestamp = this->start_timestamp+(attack*this->FPS); }

void WalkCommand::setRelease(float release){ this->release_seconds = release; }

void WalkCommand::update(bool key_pressed){
    if (key_pressed){

        if (current_time<attack_end_timestamp){
            speed=speed+1;

        }else{
            speed=speed;

        }
    } else {
            if (is_action_attack==true){
                release_end_timestamp = current_time + (release_seconds*FPS); // set Release end-time

                is_action_attack=false;
            }
            if (current_time<release_end_timestamp){
                speed=speed-1;

            }
            if (speed <=0){ 
                this->is_command_complete=true; // Setting at Parent Object level, not child level
                this->is_running=false;
                }

    }
    current_time+=1;
    std::cout << "   Speed: " << this->speed << std::endl;

    
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

int main(int argc, char *argv[]){
    std::unordered_map<std::string, ICommand*> command_map;
    float FPS=60.0f;
    Frame_Rate_Manager VariableFrameRate(FPS);
    command_map.insert_or_assign("MOVE_FORWARD", new WalkCommand(0.5f, 0.5f, FPS));
    //command_map.insert_or_assign("MOVE_BACKWARD", new WalkCommand(0.5f, 0.5f, FPS));
    //command_map.insert_or_assign("STRAFE_LEFT", new WalkCommand(0.5f, 0.5f, FPS));
    //command_map.insert_or_assign("STRAFE_RIGHT", new WalkCommand(0.5f, 0.5f, FPS));

    // Simulate Walk Action
    Uint64 walk_start = SDL_GetTicks64();
    Uint64 walk_end = walk_start+3000;  // walk for 3 seconds
    bool walk_key_pressed = true;
    command_map.at("MOVE_FORWARD")->trigger();



    
    //ICommand* action = command_map.at("MOVE_FORWARD");
    //while (!command_map.at("MOVE_FORWARD")->isComplete()){
    while (numberOfActiveCommands(command_map)>0){
        VariableFrameRate.setFrameStart();
        for (auto command:command_map){
            if (SDL_GetTicks64()<walk_end){
                walk_key_pressed=true;
                command.second->update(walk_key_pressed);
            }else{
                walk_key_pressed=false;
                command.second->update(walk_key_pressed);
            }
        }
        VariableFrameRate.setFrameEnd();
        VariableFrameRate.delay();
    }

    for (auto command:command_map){
    delete command.second;
    }

    return 0;
};
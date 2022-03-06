#include <SDL2/SDL.h>
#include <iostream>
#include "Frame_Rate_Manager.h"

class ICommand{
    public:
        virtual void execute(bool key_pressed)=0;
};

class RangeCommand:public ICommand{
    private:
        float x_range;
        float y_range;

    public:
        void execute(bool key_pressed);
};

class WalkCommand:public ICommand{
    private:
        float attack_end_timestamp; // timestamp in milliseconds
        float release_end_timestamp; // timestamp in milliseconds
        float release_seconds;
        float speed; // 0.0-1.0  0.0 is stopped, 1.0 is full speed
        float max_speed; // m/s
        bool is_action_attack;
        float FPS;
        bool action_active;
        Uint64 start_timestamp;
        Uint64 current_time;
    public:
        WalkCommand(float attack, float release, float FPS);
        bool isActive();
        void execute(bool key_pressed);
};

WalkCommand::WalkCommand(float attack, float release, float FPS){
    this->speed=0;
    this->is_action_attack=true;
    this->FPS=FPS;
    this->start_timestamp = 0;
    this->attack_end_timestamp = start_timestamp + (attack*FPS);
    this->release_seconds = release;
    this->is_action_attack=true;  // This is set to true by default and it used as a momentary switch once the Release state is triggered.
    this->current_time=start_timestamp;


}

void WalkCommand::execute(bool key_pressed){

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
            if (speed <=0){ action_active=false; }

    }
    current_time+=1;
    std::cout << "   Speed: " << this->speed << std::endl;
}

bool WalkCommand::isActive(){ return this->action_active; }




int main(int argc, char *argv[]){
    Uint64 walk_start = SDL_GetTicks64();
    float FPS=60.0f;
    float frameDelay = 1000.0f/FPS;
    Uint64 walk_end = walk_start+3000;  // walk for 10 seconds


    bool walk_key_pressed = true;
    WalkCommand action(0.5f,0.5f, FPS);
    Frame_Rate_Manager VariableFrameRate(60.0f);

    while (action.isActive()){

        VariableFrameRate.setFrameStart();
       
        if (SDL_GetTicks64()<walk_end){
            walk_key_pressed=true;
            action.execute(walk_key_pressed);
        }else{
            walk_key_pressed=false;
            action.execute(walk_key_pressed);
        }
        VariableFrameRate.setFrameEnd();
        VariableFrameRate.delay();
    }
    return 0;
};
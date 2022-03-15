
#include "actions/Action_Interface.h"
#include <string>
#include <iostream>

const bool IAction::isRunning(){ return this->is_running; }

const std::string IAction::getName() { return this->name; }

const bool IAction::isReadyToDestroy(){ return this->readyToDestroy; }

void IAction::trigger(){ 
    this->is_key_pressed=true;
    this->is_running=true; 
}




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







MoveAction::MoveAction(std::string command_name, float attack, float release, float max_speed, float FPS){
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

void MoveAction::setActionState(){
    
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

void MoveAction::setAttack(float attack){ this->attack_speed_delta = (attack * FPS)/max_speed; }

void MoveAction::setRelease(float release){ this->release_speed_delta = (release * FPS)/max_speed; }
  
    
void MoveAction::update(bool key_pressed){
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
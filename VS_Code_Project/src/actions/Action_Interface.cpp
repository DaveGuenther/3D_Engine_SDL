
#include "Action_Interface.h"
#include "../core/GameState_Observer_Pattern.h"
#include "../core/Console_Variables.h"
#include "../render/Camera.h"
#include "../globals.h"
#include <string>
#include <iostream>
#include <memory>


const bool IAction::isRunning(){ return this->is_running; }

const std::string IAction::getName() { return this->name; }

const bool IAction::isReadyToDestroy(){ return this->readyToDestroy; }

void IAction::trigger(){ 
    this->is_key_pressed=true;
    this->is_running=true; 
}

std::shared_ptr<Triangle_Modifier> IAction::getMeshModification() const{
    return mesh_modification;
}

TurnAction::TurnAction(std::string command_name, std::shared_ptr<Camera> this_camera, Vec3d direction_unit_vector, ConsoleData* my_console_data){
    this->command_name=command_name;
    this->is_key_pressed=false;
    this->is_running=false;
    this->readyToDestroy=false;
    this->mesh_modification = NULL;
    this->this_camera = this_camera;
    this->direction_unit_vector = direction_unit_vector;
    this->consoleData=my_console_data;
}

void TurnAction::update(bool key_pressed){
    // Place Holder
    if (key_pressed){ is_running=true; } else { is_running=false; }
    if (is_running){

        if (this->consoleData->logMessages.inputLogs==true) { std::cout << "Turning By Keys!"; }
        this->direction_unit_vector = this->direction_unit_vector*1.0f;
        this_camera->rotateCamera(direction_unit_vector);
    }
    is_running=false;
    this->readyToDestroy=true;

}

GameStateAction::GameStateAction(std::string command_name, GameStateSubject &subject, ConsoleData* my_console_data): subject(subject){
    this->is_key_pressed=false;
    this->is_running=false;
    this->readyToDestroy=false;
    this->mesh_modification = NULL;
    this->command_name = command_name;
    this->consoleData = my_console_data;
}

void GameStateAction::update(bool key_pressed){
    if (this->command_name=="QUIT"){
        this->subject.setState(QUIT);
        std::cout << "Goodbye!" << std::endl;   
    }else if (this->command_name=="CONSOLE"){
        SDL_StartTextInput();
        this->subject.setState(CONSOLE);
        std::cout << "Going to Console" << std::endl;
    }else if (this->command_name=="BACK_TO_GAME"){
        SDL_StopTextInput();
        this->subject.setState(IN_WORLD);
        std::cout << "Back to Game" << std::endl;
    }
    
    
    is_running=false;
}

UseAction::UseAction(std::string command_name, std::shared_ptr<Camera> this_camera, ConsoleData* my_console_data){
    this->command_name=command_name;
    this->is_key_pressed=false;
    this->is_running=false;
    this->readyToDestroy=false;
    this->mesh_modification = NULL;
    this->this_camera = this_camera;
    this->consoleData = my_console_data;
}

void UseAction::update(bool key_pressed){
    // Place Holder
    if (key_pressed){ is_running=true; } else { is_running=false; }
    if (is_running){

        if (this->consoleData->logMessages.inputLogs==true) { std::cout << "Use Pressed!"; }
        //Vec3d rotation_vector;
        //keyboardbreak=true;

        //rotation_vector.setX(1.0f);
        //rotation_vector.setY(0.0f);
        //rotation_vector.setZ(0.0f);
        //this_camera->rotateCamera(rotation_vector);
    }
    is_running=false;
    this->readyToDestroy=true;
}


JumpAction::JumpAction(std::string command_name, std::shared_ptr<Camera> this_camera, ConsoleData* my_console_data){
    //passthrough
    this->command_name=command_name;
    this->is_key_pressed=false;
    this->is_running=false;
    this->readyToDestroy=false;
    this->mesh_modification = NULL;
    this->this_camera=this_camera;
    this->consoleData = my_console_data;
}

void JumpAction::update(bool key_pressed){
    // Place Holder
    if (key_pressed){ is_running=true; } else { is_running=false; }
    if (is_running){

        if (this->consoleData->logMessages.inputLogs==true) { std::cout << "Jump Pressed!"; }
        Vec3d translation_vector;
        translation_vector.x=0.0f;
        translation_vector.y=0.01f;
        translation_vector.z=0.0f;
	    this->this_camera->setCameraPos(translation_vector);

    }
    is_running=false;
    this->readyToDestroy=true;
}

TwoAxisRangeCommand::TwoAxisRangeCommand(std::string command_name, std::shared_ptr<Camera> this_camera, float x_range, float y_range, ConsoleData* my_console_data):x_range(x_range),y_range(y_range){    
    this->command_name = command_name;
    is_running=true;
    this->mesh_modification = NULL;
    this->this_camera = this_camera;
    this->consoleData = my_console_data;
}


void TwoAxisRangeCommand::update(bool key_pressed){
    if (this->mesh_modification!=NULL){ this->mesh_modification->clearMeshAssignments();}
    if (is_running){
        if (this->consoleData->logMessages.inputLogs==true) { std::cout<< "  Applying TwoAxisMovement X: " << x_range << " Y: " << y_range; }
        Vec3d rotation_vector;
        float mouse_sensitivity=360.0f;
        rotation_vector.x=-y_range*mouse_sensitivity;
        rotation_vector.y=x_range*mouse_sensitivity;
        rotation_vector.z=0;
        this_camera->rotateCamera(rotation_vector);
        
        //mesh_modification = new Rotator(rotation_vector.getX(), rotation_vector.getY(), rotation_vector.getZ(),Vec3d(0,0,0));
        
        this->is_running=false;
    }
    //this->is_running=false;
    this->readyToDestroy=true;
}

TwoAxisRangeCommand::~TwoAxisRangeCommand(){
    //delete mesh_modification;
    
}





MoveAction::MoveAction(std::string command_name, std::shared_ptr<Camera> this_camera, Vec3d direction, float attack, float release, float max_speed, float FPS, ConsoleData* my_console_data){
    this->speed=0;
    this->is_running=false;
    this->FPS=FPS;
    this->max_speed = max_speed;
    this->attack_speed_delta = max_speed/(attack * FPS);
    this->release_speed_delta = max_speed/(release * FPS);
    this->speed;
    this->is_key_pressed=false;
    this->action_state=OFF;
    this->max_speed=max_speed;
    this->command_name = command_name;
    this->readyToDestroy=false;
    this-> direction = direction;
    this->mesh_modification = NULL;
    this->this_camera = this_camera;
    this->consoleData=my_console_data;

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
            if(speed<=0){ 
                action_state=OFF; 
                this->mesh_modification = NULL;
            }
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
    if (this->mesh_modification!=NULL){ this->mesh_modification->clearMeshAssignments();}
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
        if (this->consoleData->logMessages.inputLogs==true) { std::cout << "TRIG_ATTACK  "; }
        is_running=true;
        break;
    }
    case ATTACK:{
        if (this->consoleData->logMessages.inputLogs==true) { std::cout << "ATTACK  "; }
        speed+=attack_speed_delta;
        break;
    }
    case SUSTAIN:{
        if (this->consoleData->logMessages.inputLogs==true) { std::cout << "SUSTAIN  "; }
        speed=speed;
        break;
    }
    case TRIG_RELEASE:
        if (this->consoleData->logMessages.inputLogs==true) { std::cout << "TRIG_RELEASE  ";  }
        //Place Holder
        break;
    case RELEASE:{
        if (this->consoleData->logMessages.inputLogs==true) { std::cout << "RELEASE  "; }
        speed-=release_speed_delta;
        break;
    }
    default:
        break;
    }

    if (speed>0){ 
        Vec3d translation_vector;
        translation_vector.x=direction.x*speed;
        translation_vector.y=direction.y*speed;
        translation_vector.z=direction.z*speed;

        //Vec3d currCameraPos = this->this_camera->getCameraPos();
        //Vec3d newCameraPos = currCameraPos + translation_vector;
        //Vec3d newCameraPos = Vec3d(currCameraPos.getX()*speed, currCameraPos.getY()*speed, currCameraPos.getZ()*speed);

	    this->this_camera->setCameraPos(translation_vector);
        if (this->consoleData->logMessages.inputLogs==true) { std::cout << "    " << command_name << ": " << translation_vector.x << "," << translation_vector.y << ", " << translation_vector.z << ": " << this->speed;}
        
        /*        
        

        mesh_modification = new Translator(translation_vector.getX(), translation_vector.getY(), translation_vector.getZ());
        */
        }

    // use speed to update meshes here

    //std::cout << "    " << command_name << ": " << this->speed;
}

MoveAction::~MoveAction(){
    //delete mesh_modification;
    
}


ConsoleNavAction::ConsoleNavAction(std::string command_name, GameStateSubject &subject, ConsoleData* my_console_data){

}

void ConsoleNavAction::update(bool key_pressed){

}

ConsoleExecuteAction::ConsoleExecuteAction(std::string command_name, GameStateSubject &subject, ConsoleData* my_console_data){

}

void ConsoleExecuteAction::update(bool key_pressed){
    
}
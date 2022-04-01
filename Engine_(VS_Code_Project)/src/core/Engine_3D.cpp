#include <iostream>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>

#include "core/Engine_3D.h"
#include "core/Frame_Rate_Manager.h"
#include "core/GameState_Observer_Pattern.h"

#include "input/Event_Scanner.h"
#include "input/KeyBindings.h"
#include "input/Input_Parser.h"

#include "actions/Action_Interface.h"
#include "actions/Action_Updater.h"

#include "utility/Mesh.h"
#include "utility/Mesh_Pipeline.h"
#include "utility/Triangle_Modifier.h"

#include "render/Renderer.h"

Engine_3D::Engine_3D(void){

    SDL_Init(SDL_INIT_EVERYTHING);
    isRunning = true;
    this->Engine_Renderer = new Renderer(640,380);
    //this->game_state_subject = new GameStateSubject;
    this->Engine_State=new Game_Engine_State_Observer(game_state_subject);
    //this->my_subject.addSubscriber(this);
    this->MENU_Input_Parser = new Input_Parser(game_state_subject, Engine_Renderer, "menu_bindings.cfg");
    this->INWORLD_Input_Parser = new Input_Parser(game_state_subject, Engine_Renderer, "in_game_bindings.cfg");
    game_state_subject.setState(MENU);
    this->FPS=60;
    this->VariableFrameRate = new Frame_Rate_Manager(FPS);
    this->mesh_pipeline = new Mesh_Pipeline;
    this->INWORLD_Action_Updater = new InGame_Action_Updater(mesh_pipeline, FPS);
    
      
    game_state_subject.setState(IN_WORLD);
    
    
}

Engine_3D::~Engine_3D(){
    delete Engine_Renderer;
    delete Engine_State;
    delete MENU_Input_Parser;
    delete INWORLD_Input_Parser;
    delete VariableFrameRate;
    delete mesh_pipeline;
    delete INWORLD_Action_Updater;
}

void Engine_3D::load_meshes(){
    // Eventually allow this function to read a list of mesh file referenes and load them
    mesh_pipeline->Add_Mesh_to_Pipeline("block.mesh", Vec3d(-1.5,0.5,2));
    mesh_pipeline->Add_Mesh_to_Pipeline("pyramid.mesh", Vec3d(.5,1.5,6));
}

bool Engine_3D::is_running(){
    return isRunning;
}

void Engine_3D::engine_update(){
    
    VariableFrameRate->setFrameStart();
    //input_events->scanInput();
    switch (this->game_state_subject.getState()){
        case QUIT:
            isRunning=false;
            break;
        case IN_WORLD:{
            SDL_SetRelativeMouseMode(SDL_TRUE);
            
            INWORLD_Input_Parser->scanInput();
            INWORLD_Action_Updater->AddTactileInputMap(INWORLD_Input_Parser->getCurrentCommands());
            INWORLD_Action_Updater->AddRangeInputMap(INWORLD_Input_Parser->getRangeInput(), INWORLD_Input_Parser->didRangeInputChange());
            INWORLD_Action_Updater->update();
            mesh_pipeline->Apply_Modifications(INWORLD_Action_Updater->getModifications());
            break;
        }
        case MENU:{
            MENU_Input_Parser->scanInput();
            break;
        }
        default:
            break;
    }

    //Call Renderer
    Engine_Renderer->refreshScreen(mesh_pipeline);

    // Update Timing Loop to add delay if necessary
    VariableFrameRate->setFrameEnd();
    VariableFrameRate->delay();
}

void Engine_3D::shutdown(){
    SDL_Quit();

}
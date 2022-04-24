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
#include "render/TrianglePipeline.h"
#include "render/Camera.h"

Engine_3D::Engine_3D(void){

    SDL_Init(SDL_INIT_EVERYTHING);
    isRunning = true;
    player_camera = new Camera();
    this->Engine_Renderer = new Renderer(640,380, player_camera);

    this->Engine_State=new Game_Engine_State_Observer(game_state_subject);

    this->MENU_Input_Parser = new Input_Parser(game_state_subject, Engine_Renderer, "menu_bindings.cfg");
    this->INWORLD_Input_Parser = new Input_Parser(game_state_subject, Engine_Renderer, "in_game_bindings.cfg");
    game_state_subject.setState(MENU);
    this->FPS=60.0f;
    this->VariableFrameRate = new Frame_Rate_Manager(FPS);
    this->mesh_pipeline = new Mesh_Pipeline;
    this->INWORLD_Action_Updater = new InGame_Action_Updater(mesh_pipeline, player_camera, FPS);
    
      
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

    // call Pre-Renderer - This will remove triangles from meshes and order from farthest to nearest (positive to negative).  
    // Rather than pass triangles in a mesh pipeline organized by meshes, it will pass a triangle pipeline
    TrianglePipeline* my_tri_renderer = new TrianglePipeline();
    my_tri_renderer->setPipelineFromMeshes(mesh_pipeline);

    //CAMERA OVERRIDE for testing
	//Vec3d tempCamera = player_camera->getCameraPos();
	//player_camera->setCameraPos(Vec3d(0.0f,tempCamera.getY()+0.001,0.0f));    

    //Call Renderer
    Engine_Renderer->refreshScreen(my_tri_renderer);

    // Update Timing Loop to add delay if necessary
    VariableFrameRate->setFrameEnd();
    VariableFrameRate->delay();
    std::string window_title = "3D World - FPS: " + std::to_string(int(VariableFrameRate->getMeasuredFPS()));
    Engine_Renderer->setWindowTitle(window_title);
}

void Engine_3D::shutdown(){
    SDL_Quit();

}
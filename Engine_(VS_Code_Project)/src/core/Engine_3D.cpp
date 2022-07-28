#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>

#include "SDL.h"

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
#include "render/AspectRatio.h"

Engine_3D::Engine_3D(void){

    SDL_Init(SDL_INIT_EVERYTHING);
    isRunning = true;
    float aspectRatio = AspectRatio::getAspectRatio(640,380);
    std::shared_ptr<Camera> player_camera(new Camera(aspectRatio));
    player_camera = player_camera;
    std::shared_ptr<Renderer> this_Renderer(new Renderer(640, 380, player_camera));
    this->Engine_Renderer=this_Renderer;
    this_Renderer->setColorFrustumClippedTris(false); // don't show RGB clipped tris.  Instead show intended color



    std::shared_ptr<Game_Engine_State_Observer> Engine_State(new Game_Engine_State_Observer(game_state_subject));
    this->Engine_State=Engine_State;
    std::shared_ptr<Input_Parser> MENU_Input_Parser(new Input_Parser(game_state_subject, Engine_Renderer, "menu_bindings.cfg"));
    this->MENU_Input_Parser = MENU_Input_Parser;
    std::shared_ptr<Input_Parser> INWORLD_Input_Parser(new Input_Parser(game_state_subject, Engine_Renderer, "in_game_bindings.cfg"));
    this->INWORLD_Input_Parser = INWORLD_Input_Parser;

    game_state_subject.setState(MENU);
    this->FPS=60.0f;
    std::shared_ptr<Frame_Rate_Manager> VariableFrameRate(new Frame_Rate_Manager(FPS));
    this->VariableFrameRate = VariableFrameRate;
    std::shared_ptr<TextureList> texture_list(new TextureList());
    this->texture_list = texture_list;
    std::shared_ptr<Mesh_Pipeline> local_mesh_pipeline(new Mesh_Pipeline(texture_list));
    this->mesh_pipeline = local_mesh_pipeline;



    std::shared_ptr<InGame_Action_Updater> INWORLD_Action_Updater(new InGame_Action_Updater(this->mesh_pipeline, player_camera, FPS, game_state_subject));
    this->INWORLD_Action_Updater = INWORLD_Action_Updater;
      
    game_state_subject.setState(IN_WORLD);

    
}

Engine_3D::~Engine_3D(){

    
}

void Engine_3D::load_meshes(){
    // Eventually allow this function to read a list of mesh file referenes and load them
    //mesh_pipeline->Add_OBJ_Mesh_to_Pipeline("cave2lowpoly.obj", Vec3d(0,0,0));
    //mesh_pipeline->Add_OBJ_Mesh_to_Pipeline("textured_cube.obj", Vec3d(0,0,5));
    mesh_pipeline->Add_OBJ_Mesh_to_Pipeline("rainbow_cube(zFor_yUp).obj", Vec3d(2,0,2.1));
    //mesh_pipeline->Add_OBJ_Mesh_to_Pipeline("Pirate Cave.obj", Vec3d(0,0,0));
    //mesh_pipeline->Add_OBJ_Mesh_to_Pipeline("compass.obj", Vec3d(0,0,0));
    //mesh_pipeline->Add_OBJ_Mesh_to_Pipeline("funky_little_thing.obj", Vec3d(-1.5,0.5,5));
    //mesh_pipeline->Add_Mesh_to_Pipeline("block.mesh", Vec3d(-1.5,0.5,2));
    //mesh_pipeline->Add_Mesh_to_Pipeline("pyramid.mesh", Vec3d(4.5,1.5,10));
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
    std::shared_ptr<TrianglePipeline> my_tri_renderer(new TrianglePipeline());
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
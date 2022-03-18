#include "Engine_3D.h"
#include <SDL2/SDL.h>
#include "input/Event_Scanner.h"
#include "input/KeyBindings.h"
#include "GameState_Observer_Pattern.h"
#include "input/Input_Parser.h"
#include <iostream>
#include <unordered_map>
#include "Frame_Rate_Manager.h"
#include "actions/Action_Interface.h"
#include "actions/Action_Updater.h"
#include <vector>
#include "Mesh.h"
#include "Renderer.h"
#include "Mesh_Pipeline.h"
#include "Triangle_Modifier.h"

Engine_3D::Engine_3D(void){

    SDL_Init(SDL_INIT_EVERYTHING);
    isRunning = true;

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

void Engine_3D::load_meshes(){
    // Eventually allow this function to read a list of mesh file referenes and load them
    mesh_pipeline->Add_Mesh_to_Pipeline("block.mesh");
    mesh_pipeline->Add_Mesh_to_Pipeline("pyramid.mesh");
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
            INWORLD_Input_Parser->scanInput();
            INWORLD_Action_Updater->AddTactileInputMap(INWORLD_Input_Parser->getCurrentCommands());
            INWORLD_Action_Updater->AddRangeInputMap(INWORLD_Input_Parser->getRangeInput());
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

    VariableFrameRate->setFrameEnd();
    VariableFrameRate->delay();

    //Call Renderer
    Engine_Renderer.Refresh_Screen(mesh_pipeline);







    /*


    int i;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
            if (event.key.keysym.sym == SDLK_q)
            {
                modifications.clear();
                modifications.push_back(new Translator(0,0.1,0));
                for(i=0;i<mesh_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}

                mesh_pipeline.Apply_Modifications(modifications);

                
            }

            if (event.key.keysym.sym == SDLK_e)
            {
                modifications.clear();
                modifications.push_back(new Translator(0,-0.1,0));
                for(i=0;i<mesh_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}

                mesh_pipeline.Apply_Modifications(modifications);

                
            }

            if (event.key.keysym.sym == SDLK_d)
            {
                modifications.clear();
                modifications.push_back(new Translator(.1,0,0));
                for(i=0;i<mesh_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}

                mesh_pipeline.Apply_Modifications(modifications);

                
            }


            if (event.key.keysym.sym == SDLK_a)
            {
                modifications.clear();
                modifications.push_back(new Translator(-.1,0,0));		
                for(i=0;i<mesh_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}	
                //modifications.push_back(new Rotator(0,-10,0,Vec3d(0,0,0)));
                //modifications.back()->AssignToMesh(0);
                //modifications.push_back(new Rotator(0,10,0,Vec3d(0,0,0)));
                //modifications.back()->AssignToMesh(1);	
                mesh_pipeline.Apply_Modifications(modifications);

                
            }

            if (event.key.keysym.sym == SDLK_w)
            {
                modifications.clear();
                modifications.push_back(new Translator(0,0,-.1));	
                for(i=0;i<mesh_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}	
                //modifications.push_back(new Rotator(-10,0,0,Vec3d(0,0,0)));
                //modifications.back()->AssignToMesh(0);
                //modifications.push_back(new Rotator(10,0,0,Vec3d(0,0,0)));
                //modifications.back()->AssignToMesh(1);				
                mesh_pipeline.Apply_Modifications(modifications);

                
            }
            
            if (event.key.keysym.sym == SDLK_s)
            {
                modifications.clear();
                modifications.push_back(new Translator(0,0,0.1));		
                for(i=0;i<mesh_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
                //modifications.push_back(new Rotator(10,0,0,Vec3d(0,0,0)));
                //modifications.back()->AssignToMesh(0);
                //modifications.push_back(new Rotator(-10,0,0,Vec3d(0,0,0)));
                //modifications.back()->AssignToMesh(1);				
                mesh_pipeline.Apply_Modifications(modifications);

                
            }

            if (event.key.keysym.sym == SDLK_UP)
            {
                modifications.clear();
                modifications.push_back(new Rotator(2,0,0,Vec3d(0,0,0)));
                //for(i=0;i<mesh_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
                modifications.back()->AssignToMesh(1);
                mesh_pipeline.Apply_Modifications(modifications);

                
            }                
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                modifications.clear();
                modifications.push_back(new Rotator(-2,0,0,Vec3d(0,0,0)));
                //for(i=0;i<mesh_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
                modifications.back()->AssignToMesh(1);

                mesh_pipeline.Apply_Modifications(modifications);

                
            }     
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                modifications.clear();
                modifications.push_back(new Rotator(0,-2,0,Vec3d(0,0,0)));
                //for(i=0;i<mesh_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
                modifications.back()->AssignToMesh(1);

                mesh_pipeline.Apply_Modifications(modifications);

                
            }     
            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                modifications.clear();
                modifications.push_back(new Rotator(0,2,0,Vec3d(0,0,0)));
                //for(i=0;i<mesh_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
                modifications.back()->AssignToMesh(1);

                mesh_pipeline.Apply_Modifications(modifications);

                
            }                     
        }		
    }


    // Calculate Rotations
    // Rotator_Service::Rotate_Pipeline(mesh_pipeline);

    // Calculate Tranlations
    		

    // Establish Projection on mesh pipeline
    //  Find a way to pass mesh_pipeline to Renderer::Updatecreen wihout errors...
    */
}

void Engine_3D::shutdown(){
    SDL_Quit();

}
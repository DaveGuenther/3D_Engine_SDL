#include <vector>
#include <SDL2/SDL.h>
#include "Mesh.h"
#include "Renderer.h"
#include "Engine_3D.h"
#include "Rotator_Service.h"
#include "Mesh_Pipeline.h"

Engine_3D::Engine_3D(void){

    SDL_Init(SDL_INIT_EVERYTHING);
    isRunning = true;
    
    

}

void Engine_3D::load_meshes(){
    // Eventually allow this function to read a list of mesh file referenes and load them
    mesh_pipeline.Add_Mesh_to_Pipeline("block.mesh");
}

bool Engine_3D::is_running(){
    return isRunning;
}

void Engine_3D::engine_update(){
    
    float fTheta, tTheta=45.0f;

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

            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                fTheta +=1;
                
                mesh_pipeline.Set_Rot_Angle_Changes_for_Pipeline(fTheta, 0);
                
            }
            
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                fTheta -=1;
                mesh_pipeline.Set_Rot_Angle_Changes_for_Pipeline(fTheta, 0);
                
            }

            if (event.key.keysym.sym == SDLK_UP)
            {
                tTheta +=1;
                mesh_pipeline.Set_Rot_Angle_Changes_for_Pipeline(0, tTheta);
            }
            
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                tTheta -=1;
                mesh_pipeline.Set_Rot_Angle_Changes_for_Pipeline(0, tTheta);
                
            }
        }
    }


    // Calculate Rotations
    Rotator_Service::Rotate_Pipeline(mesh_pipeline);

    // Calculate Tranlations

    // Establish Projection on mesh pipeline
    Engine_Renderer.Refresh_Screen(mesh_pipeline);
    ///  Find a way to pass mesh_pipeline to Renderer::Updatecreen wihout errors...

}

void Engine_3D::shutdown(){
    SDL_Quit();

}
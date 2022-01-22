#include <vector>
#include <SDL2/SDL.h>
#include "Mesh.h"
#include "Renderer.h"
#include "Engine_3D.h"

Engine_3D::Engine_3D(void){

    SDL_Init(SDL_INIT_EVERYTHING);
    isRunning = true;
    
    

}

void Engine_3D::load_meshes(){

    
	mesh_pipeline.push_back(Mesh());
    mesh_pipeline.back().Load_Mesh("block.mesh");

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
                
            }
            
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                fTheta -=1;
                
            }

            if (event.key.keysym.sym == SDLK_UP)
            {
                tTheta +=1;
                
            }
            
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                tTheta -=1;
                
            }
        }
    }
    // Calculate Tranlations

    // Calculate Rotations

    // Establish Projection on mesh pipeline
    Engine_Renderer.UpdateScreen(mesh_pipeline);
    ///  Find a way to pass mesh_pipeline to Renderer::Updatecreen wihout errors...

}

void Engine_3D::shutdown(){
    SDL_Quit();

}
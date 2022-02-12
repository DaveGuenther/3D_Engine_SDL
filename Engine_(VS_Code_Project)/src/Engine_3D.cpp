#include <vector>
#include <SDL2/SDL.h>
#include "Mesh.h"
#include "Renderer.h"
#include "Engine_3D.h"
///#include "Rotator_Service.h"
#include "Mesh_Pipeline.h"
#include "Triangle_Modifier.h"

Engine_3D::Engine_3D(void){

    SDL_Init(SDL_INIT_EVERYTHING);
    isRunning = true;

    
    
}

void Engine_3D::load_meshes(){
    // Eventually allow this function to read a list of mesh file referenes and load them
    my_pipeline.Add_Mesh_to_Pipeline("block.mesh");
    my_pipeline.Add_Mesh_to_Pipeline("pyramid.mesh");
}

bool Engine_3D::is_running(){
    return isRunning;
}

void Engine_3D::engine_update(){
    
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
                for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}

                my_pipeline.Apply_Modifications(modifications);

                
            }

            if (event.key.keysym.sym == SDLK_e)
            {
                modifications.clear();
                modifications.push_back(new Translator(0,-0.1,0));
                for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}

                my_pipeline.Apply_Modifications(modifications);

                
            }

            if (event.key.keysym.sym == SDLK_d)
            {
                modifications.clear();
                modifications.push_back(new Translator(.1,0,0));
                for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}

                my_pipeline.Apply_Modifications(modifications);

                
            }


            if (event.key.keysym.sym == SDLK_a)
            {
                modifications.clear();
                modifications.push_back(new Translator(-.1,0,0));		
                for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}	
                //modifications.push_back(new Rotator(0,-10,0,Vec3d(0,0,0)));
                //modifications.back()->AssignToMesh(0);
                //modifications.push_back(new Rotator(0,10,0,Vec3d(0,0,0)));
                //modifications.back()->AssignToMesh(1);	
                my_pipeline.Apply_Modifications(modifications);

                
            }

            if (event.key.keysym.sym == SDLK_w)
            {
                modifications.clear();
                modifications.push_back(new Translator(0,0,-.1));	
                for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}	
                //modifications.push_back(new Rotator(-10,0,0,Vec3d(0,0,0)));
                //modifications.back()->AssignToMesh(0);
                //modifications.push_back(new Rotator(10,0,0,Vec3d(0,0,0)));
                //modifications.back()->AssignToMesh(1);				
                my_pipeline.Apply_Modifications(modifications);

                
            }
            
            if (event.key.keysym.sym == SDLK_s)
            {
                modifications.clear();
                modifications.push_back(new Translator(0,0,0.1));		
                for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
                //modifications.push_back(new Rotator(10,0,0,Vec3d(0,0,0)));
                //modifications.back()->AssignToMesh(0);
                //modifications.push_back(new Rotator(-10,0,0,Vec3d(0,0,0)));
                //modifications.back()->AssignToMesh(1);				
                my_pipeline.Apply_Modifications(modifications);

                
            }

            if (event.key.keysym.sym == SDLK_UP)
            {
                modifications.clear();
                modifications.push_back(new Rotator(2,0,0,Vec3d(0,0,0)));
                //for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
                modifications.back()->AssignToMesh(1);
                my_pipeline.Apply_Modifications(modifications);

                
            }                
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                modifications.clear();
                modifications.push_back(new Rotator(-2,0,0,Vec3d(0,0,0)));
                //for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
                modifications.back()->AssignToMesh(1);

                my_pipeline.Apply_Modifications(modifications);

                
            }     
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                modifications.clear();
                modifications.push_back(new Rotator(0,-2,0,Vec3d(0,0,0)));
                //for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
                modifications.back()->AssignToMesh(1);

                my_pipeline.Apply_Modifications(modifications);

                
            }     
            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                modifications.clear();
                modifications.push_back(new Rotator(0,2,0,Vec3d(0,0,0)));
                //for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
                modifications.back()->AssignToMesh(1);

                my_pipeline.Apply_Modifications(modifications);

                
            }                     
        }		
    }


    // Calculate Rotations
    // Rotator_Service::Rotate_Pipeline(mesh_pipeline);

    // Calculate Tranlations
    Engine_Renderer.Refresh_Screen(my_pipeline);		

    // Establish Projection on mesh pipeline
    //  Find a way to pass mesh_pipeline to Renderer::Updatecreen wihout errors...

}

void Engine_3D::shutdown(){
    SDL_Quit();

}
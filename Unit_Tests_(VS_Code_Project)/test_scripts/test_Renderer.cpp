#include <SDL2/SDL.h>
#include "Renderer.h"
#include "Mesh_Pipeline.h"
#include "Triangle_Modifier.h"

int main (int argc, char *argv[]){
    
    SDL_Init(SDL_INIT_EVERYTHING);
    Renderer Engine_Renderer;

    Mesh_Pipeline my_pipeline;
    my_pipeline.Add_Mesh_to_Pipeline("block.mesh");
    my_pipeline.Add_Mesh_to_Pipeline("pyramid.mesh");
    
    float x_deg=20;
    float y_deg=0;
    float z_deg=20;
    Vec3d center=Vec3d(0,0,0);
    int i;
    std::vector<Triangle_Modifier*> modifications;
    //modifications.push_back(new Translator(1, 0, 1));
    
    //for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
    //modifications.push_back(new Rotator(x_deg, y_deg, z_deg, center));



    //Triangle my_triangle(Vec3d(0.5f,0.6f,0.7f),Vec3d(1.1f,1.2f,1.3f), Vec3d(2.4f,2.5f,2.6f), 3);
    //std::cout << my_triangle.toString() << std::endl;
    bool isRunning = true;
	SDL_Event event;

    while (isRunning)
	{
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
			
    Engine_Renderer.Refresh_Screen(my_pipeline);		
    }


    SDL_Quit();

    return 0;
}
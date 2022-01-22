#include <SDL2/SDL.h>
#include "Renderer.h"
#include "Triangle.h"

//Public Methods
Renderer::Renderer(void){
    // SDL and Screen initializing
	SCREEN_W = 640;
    SCREEN_H = 360;
	window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, screen_mode);
	renderer = SDL_CreateRenderer(window, -1, 0);
    

	// Projection Matrix
    fNear = 0.1f;
	fFar = 1000.0f;
	fFOV=90.0f;
	fAspectRatio = (float)SCREEN_H/(float)SCREEN_W;
	fFOV_rad = 1.0/(SDL_tanf((fFOV/2)*(3.14159265f/180.0f)));

	matProj.m[0][0] = fAspectRatio*fFOV_rad;
	matProj.m[1][0] = 0.0;
	matProj.m[2][0] = 0.0;
	matProj.m[3][0] = 0.0;
	matProj.m[0][1] = 0.0;
	matProj.m[1][1] = fFOV_rad;
	matProj.m[2][1] = 0.0;
	matProj.m[3][1] = 0.0;
	matProj.m[0][2] = 0.0;
	matProj.m[1][2] = 0.0;
	matProj.m[2][2] = fFar/(fFar-fNear);
	matProj.m[3][2] = (-fFar*fNear)/(fFar-fNear);
	matProj.m[0][3] = 0.0;
	matProj.m[1][3] = 0.0;
	matProj.m[2][3] = 1.0;
	matProj.m[3][3] = 0.0;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

}
//void UpdateScreen(std::vector<Mesh>& mesh_pipe)
void Renderer::UpdateScreen(const std::vector<Mesh> &mesh_pipe){
	for (auto this_mesh: mesh_pipe){
		std::vector<Triangle> tris = this_mesh.get_tris();

	}
} 

//Private Methods
Vec2d Renderer::cart_to_screen(Vec2d this_point)
{
	float HALF_SCREEN_W = (SCREEN_W)/2;
	float scaled_x = this_point.x*(HALF_SCREEN_W);
	this_point.x = scaled_x+(HALF_SCREEN_W);

	float HALF_SCREEN_H = (SCREEN_H)/2;
	float scaled_y = this_point.y*(HALF_SCREEN_H);
	this_point.y = SCREEN_H-(scaled_y+(HALF_SCREEN_H));
	return this_point;
} 

void Renderer::shutdown(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	

}
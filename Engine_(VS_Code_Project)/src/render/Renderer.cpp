#include <SDL2/SDL.h>

#include "utility/Vec2d.h"
#include "utility/Triangle.h"
#include "utility/Mesh_Pipeline.h"
#include "utility/Multiply_Matrix_Service.h"
#include "utility/Vector_Math_Service.h"
#include "render/Renderer.h"

Renderer::Renderer(int SCREEN_W, int SCREEN_H) {
    // SDL and Screen initializing
	this->SCREEN_W = SCREEN_W;
    this->SCREEN_H = SCREEN_H;
	window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, screen_mode);
	renderer = SDL_CreateRenderer(window, -1, 0);
    

	// Projection Matrix
    fNear = 0.1f;
	fFar = 1000.0f;
	fFOV=80.0f;
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
	//SDL_WarpMouseInWindow(this->window, SCREEN_W/2, SCREEN_H/2);

	camera.setX(0);
	camera.setY(0);
	camera.setZ(0);

}

void Renderer::resetMouseXY(){
	SDL_WarpMouseInWindow(this->window, SCREEN_W/2, SCREEN_H/2);
}

void Renderer::drawTriangle2d(Vec2d vert1, Vec2d vert2, Vec2d vert3, SDL_Color col)
{
	
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);

	vert1 = cartesianToScreen(vert1);
	vert2 = cartesianToScreen(vert2);
	vert3 = cartesianToScreen(vert3);
	SDL_RenderDrawLineF(renderer, vert1.getX(), vert1.getY(), vert2.getX(), vert2.getY());
	SDL_RenderDrawLineF(renderer, vert2.getX(), vert2.getY(), vert3.getX(), vert3.getY());
	SDL_RenderDrawLineF(renderer, vert3.getX(), vert3.getY(), vert1.getX(), vert1.getY());
}

void Renderer::projectTriangle3d(Triangle &tri){
	// Apply Perspective Projection Matrix
	Triangle triProjected;
	Vec3d pt0; 
	Vec3d pt1; 
	Vec3d pt2;
	
	Vec3d TriPoint0 = tri.getTrianglePoint(0);
	Vec3d TriPoint1 = tri.getTrianglePoint(1);
	Vec3d TriPoint2 = tri.getTrianglePoint(2);

	// Calculate Normals and Backface Culling
	
	Vec3d line1 = Vec3d(TriPoint1.getX()-TriPoint0.getX(), TriPoint1.getY()-TriPoint0.getY(), TriPoint1.getZ()-TriPoint0.getZ());
	Vec3d line2 = Vec3d(TriPoint2.getX()-TriPoint0.getX(), TriPoint2.getY()-TriPoint0.getY(), TriPoint2.getZ()-TriPoint0.getZ());
	Vec3d normal_vector = VectorMathService::crossProduct(line1, line2);
	VectorMathService::getUnitVector(normal_vector);

	// perform dot product here and test <0
	Vec3d camera_to_triangle_vector = Vec3d(TriPoint0.getX()-camera.getX(), TriPoint0.getY()-camera.getY(), TriPoint0.getY()-camera.getY()); 
	VectorMathService::getUnitVector(camera_to_triangle_vector);
	if (VectorMathService::dotProduct(normal_vector, camera_to_triangle_vector)<0.0f){ // Checks to see if normal vector >= 90 degs away from camera to triangle view vector
		Multiply_Matrix_Service::MultiplyMatrixVector(TriPoint0, pt0, matProj);
		Multiply_Matrix_Service::MultiplyMatrixVector(TriPoint1, pt1, matProj);
		Multiply_Matrix_Service::MultiplyMatrixVector(TriPoint2, pt2, matProj);
		triProjected.setTrianglePoint(0,pt0);
		triProjected.setTrianglePoint(1,pt1);
		triProjected.setTrianglePoint(2,pt2);

		// Drop 3D to 2D
		Vec2d point1, point2, point3;

		point1.setX(triProjected.getTrianglePoint(0).getX());
		point1.setY(triProjected.getTrianglePoint(0).getY());

		point2.setX(triProjected.getTrianglePoint(1).getX());
		point2.setY(triProjected.getTrianglePoint(1).getY());

		point3.setX(triProjected.getTrianglePoint(2).getX());
		point3.setY(triProjected.getTrianglePoint(2).getY());			

		SDL_Color col;
		col.r=255; col.g=0; col.b=0; col.a = 255;

		drawTriangle2d(point1, point2, point3, col);
	}
}

void Renderer::refreshScreen(Mesh_Pipeline* this_mesh_pipeline){
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);	
	Mesh_Pipeline mesh_pipeline = *this_mesh_pipeline;
	for (auto this_mesh: mesh_pipeline.Get_Meshes()){  //Issues with mesh_pipeline.Get_Meshes() if I try to make this_mesh_pipeline a const ptr
		std::vector<Triangle> tris = this_mesh.getTriangles();
		for (auto tri: tris)
		{
			projectTriangle3d(tri);
		
		}
	}
	drawReticle();
	SDL_RenderPresent(renderer);
	//SDL_WarpMouseInWindow(this->window, SCREEN_W/2, SCREEN_H/2);
} 

void Renderer::drawReticle(){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	// Draw Reticle
	Vec2d single_point;
	single_point.setX(0);
	single_point.setY(0);
	single_point = cartesianToScreen(single_point);

	float x = single_point.getX();
	float y = single_point.getY();
	SDL_RenderDrawPointF(renderer, x, y);
}

//Private Methods
Vec2d Renderer::cartesianToScreen(Vec2d this_point)
{
	float HALF_SCREEN_W = (SCREEN_W)/2;
	float scaled_x = this_point.getX()*(HALF_SCREEN_W);
	this_point.setX(scaled_x+(HALF_SCREEN_W));

	float HALF_SCREEN_H = (SCREEN_H)/2;
	float scaled_y = this_point.getY()*(HALF_SCREEN_H);
	this_point.setY(SCREEN_H-(scaled_y+(HALF_SCREEN_H)));
	return this_point;
} 

const int Renderer::getWindowWidth()const { return SCREEN_W; }
const int Renderer::getWindowHeight()const { return SCREEN_H; }

void Renderer::shutdown(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	

}
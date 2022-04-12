#include <SDL2/SDL.h>
#include <map>

#include "utility/Vec2d.h"
#include "utility/Triangle.h"
#include "utility/Mesh_Pipeline.h"
#include "utility/Vector_Math_Service.h"
#include "utility/Mat4x4.h"
#include "render/Renderer.h"
#include "render/Rasterizer.h"


Renderer::Renderer(int SCREEN_W, int SCREEN_H) {
    // SDL and Screen initializing
	this->SCREEN_W = SCREEN_W;
    this->SCREEN_H = SCREEN_H;
	window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, screen_mode);
	renderer = SDL_CreateRenderer(window, -1, 0);
    

	// Projection Matrix
	fNear = 0.1f;
	fFar = 1000.0f;
	fFOV=90.0f;
	matProj = Mat4x4::matrixMakeProjection(fFOV, SCREEN_W, SCREEN_H, fNear, fFar);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	//SDL_WarpMouseInWindow(this->window, SCREEN_W/2, SCREEN_H/2);

	camera.setX(0);
	camera.setY(0);
	camera.setZ(0);

}

void Renderer::setWindowTitle(std::string title){
	char* c = const_cast<char*>(title.c_str());
	SDL_SetWindowTitle(this->window, c);
}

void Renderer::resetMouseXY(){
	SDL_WarpMouseInWindow(this->window, SCREEN_W/2, SCREEN_H/2);
}

SDL_Color Renderer::applyDepthDimmer(Triangle& this_tri, SDL_Color col){
    float z_center = this_tri.getTriangleZCenter();
	
    float color_modifier;
    if (z_center>=this->max_visible_z_depth){
        color_modifier = this->min_visible_color_modifier;
    }else{
        color_modifier = 1-(z_center/this->max_visible_z_depth);
		if (color_modifier<min_visible_color_modifier) { color_modifier=min_visible_color_modifier; }
    }
    SDL_Color draw_col;
    draw_col.r= col.r*color_modifier;
    draw_col.g= col.g*color_modifier;
    draw_col.b= col.b*color_modifier;
    draw_col.a=255;
	//std::cout << z_center << " " << color_modifier << std::endl; 
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    return draw_col;
		
}

void Renderer::drawWireFrameTriangle2d(Triangle this_triangle, SDL_Color col)
{
	
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
	Vec2d vert1, vert2, vert3;
	vert1 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(0).getX(), this_triangle.getTrianglePoint(0).getY()));
	vert2 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(1).getX(), this_triangle.getTrianglePoint(1).getY()));
	vert3 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(2).getX(), this_triangle.getTrianglePoint(2).getY()));
	SDL_RenderDrawLineF(renderer, vert1.getX(), vert1.getY(), vert2.getX(), vert2.getY());
	SDL_RenderDrawLineF(renderer, vert2.getX(), vert2.getY(), vert3.getX(), vert3.getY());
	SDL_RenderDrawLineF(renderer, vert3.getX(), vert3.getY(), vert1.getX(), vert1.getY());
}

void Renderer::drawFilledTriangle2d(Triangle this_triangle, SDL_Color col){
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
    
	//convert triangle x and y coords to pixel screen coords
	Vec2d vert1, vert2, vert3;
	vert1 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(0).getX(), this_triangle.getTrianglePoint(0).getY()));
	vert2 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(1).getX(), this_triangle.getTrianglePoint(1).getY()));
	vert3 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(2).getX(), this_triangle.getTrianglePoint(2).getY()));

	Triangle screenTri(Vec3d(vert1.getX(),vert1.getY(),this_triangle.getTrianglePoint(0).getZ()), 
						Vec3d(vert2.getX(),vert2.getY(),this_triangle.getTrianglePoint(1).getZ()),
						Vec3d(vert3.getX(),vert3.getY(),this_triangle.getTrianglePoint(2).getZ()),0);

	//rasterize triangle In Out
	//ITriangleRasterizer* this_inout_rasterizer = new InOutRasterizer(renderer);
	//this_inout_rasterizer->drawTriangle(screenTri,col);

	//rasterie triangle with ScanLines
	ITriangleRasterizer* this_scanline_rasterizer = new ScanlineRasterizer(renderer);
	this_scanline_rasterizer->drawTriangle(screenTri, col);

}

void Renderer::buildCameraMatrix(Vec3d camera){
	Vec3d lookVector = Vec3d (0.0f,0.0f,1.0f); // This need to be not hard coded!
	Vec3d vUp=Vec3d(0.0f,1.0f,0.0f);
	Vec3d vTarget = camera+lookVector;

	Mat4x4 matCamera = Mat4x4::matrixPointAt(camera, vTarget, vUp);

	this->matView = Mat4x4::matrixLookAt(matCamera);

}

void Renderer::setCamera(Vec3d camera){
	this->camera = camera;
}

void Renderer::projectTriangle3d(Triangle &tri){
	// Apply Perspective Projection Matrix
	Triangle triProjected, triView;
	Vec3d pt0; 
	Vec3d pt1; 
	Vec3d pt2;
	
	Vec3d TriPoint0 = tri.getTrianglePoint(0);
	Vec3d TriPoint1 = tri.getTrianglePoint(1);
	Vec3d TriPoint2 = tri.getTrianglePoint(2);


	// Calculate Normals and Backface Culling
	
	Vec3d line1 = TriPoint1-TriPoint0;
	Vec3d line2 = TriPoint2-TriPoint1;
	
	Vec3d normal_vector = VectorMathService::crossProduct(line1, line2);
	VectorMathService::getUnitVector(normal_vector);

	// perform dot product here and test <0 
	Vec3d camera_to_triangle_vector = TriPoint0-camera;
	VectorMathService::getUnitVector(camera_to_triangle_vector);
	if (VectorMathService::dotProduct(normal_vector, camera_to_triangle_vector)<0.0f){ // Checks to see if normal vector >= 90 degs away from camera to triangle view vector
		
		// Project worldspace to Camera view
		triView.setTrianglePoint(0, VectorMathService::MultiplyMatrixVector(matView, TriPoint0));
		triView.setTrianglePoint(1, VectorMathService::MultiplyMatrixVector(matView, TriPoint1));
		triView.setTrianglePoint(2, VectorMathService::MultiplyMatrixVector(matView, TriPoint2));


		TriPoint0 = triView.getTrianglePoint(0)-this->camera;
		TriPoint1 = triView.getTrianglePoint(1)-this->camera;
		TriPoint2 = triView.getTrianglePoint(2)-this->camera;


		pt0 = VectorMathService::MultiplyMatrixVector(matProj, TriPoint0);
		pt1 = VectorMathService::MultiplyMatrixVector(matProj, TriPoint1);
		pt2 = VectorMathService::MultiplyMatrixVector(matProj, TriPoint2);
		pt0 = pt0/pt0.getW();
		pt1 = pt1/pt1.getW();
		pt2 = pt2/pt2.getW();

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

		SDL_Color col; col.r=255; col.g=255; col.b=255; col.a = 255;
		SDL_Color dimmed_col = applyDepthDimmer(tri, col);

		//drawWireFrameTriangle2d(triProjected, col);
		drawFilledTriangle2d(triProjected,dimmed_col);
	}
}

void Renderer::refreshScreen(RendererPipeline* my_pre_renderer){
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);	
	this->setCamera(Vec3d(0.0f,this->camera.getY()+0.001,0.0f));
	std::cout << this->camera.toString() << std::endl;
	this->buildCameraMatrix(this->camera);
	for (auto tri: my_pre_renderer->getOrderedTriangles())
	{
		
		projectTriangle3d(tri);
	}

	drawReticle();
	SDL_RenderPresent(renderer);

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
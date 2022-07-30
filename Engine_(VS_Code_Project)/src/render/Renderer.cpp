#include "SDL.h"
#include <map>
#include <string>
#include <iostream>

#include "utility/Vec2d.h"
#include "utility/Triangle.h"
#include "utility/Mesh_Pipeline.h"
#include "utility/Vector_Math_Service.h"
#include "utility/nonVector_Math_Service.h"
#include "utility/Mat4x4.h"
#include "render/Renderer.h"
#include "render/Rasterizer.h"
#include "render/Clipper.h"
#include "render/Frustum.h"
#include "render/AspectRatio.h"
#include "globals.h"


Renderer::Renderer(int SCREEN_W, int SCREEN_H, std::shared_ptr<Camera> player_camera) {
    // SDL and Screen initializing
	this->SCREEN_W = SCREEN_W;
    this->SCREEN_H = SCREEN_H;
	window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, screen_mode);
	renderer = SDL_CreateRenderer(window, -1, 0);
    

	// Projection Matrix
	fNear = 0.1f;
	fFar = 500.0f;
	fFOV=70.0f;
	this->fAspectRatio = AspectRatio::getAspectRatio(SCREEN_W, SCREEN_H);
	matProj = Mat4x4::matrixMakeProjection(fFOV, SCREEN_W, SCREEN_H, fNear, fFar);
	

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	//SDL_WarpMouseInWindow(this->window, SCREEN_W/2, SCREEN_H/2);

	this->player_camera = player_camera;
	std::shared_ptr<Clipper> thisFrustumClipper(new Clipper(player_camera));
	this->thisFrustumClipper = thisFrustumClipper;

	this->min_blue_value = 255*this->min_visible_color_modifier;
	this->min_red_value = 255*this->min_visible_color_modifier;
	this->min_green_value = 255*this->min_visible_color_modifier;

}

void Renderer::setWindowTitle(std::string title){
	char* c = const_cast<char*>(title.c_str());
	SDL_SetWindowTitle(this->window, c);
}

void Renderer::resetMouseXY(){
	SDL_WarpMouseInWindow(this->window, SCREEN_W/2, SCREEN_H/2);
}

SDL_Color Renderer::applyDepthDimmer(Triangle& this_tri){
    float z_center = this_tri.getTriangleZCenter();
	SDL_Color col = this_tri.getColor();
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

	if (draw_col.r<this->min_red_value) {draw_col.r=this->min_red_value;}
	if (draw_col.g<this->min_red_value) {draw_col.g=this->min_green_value;}
	if (draw_col.b<this->min_red_value) {draw_col.b=this->min_blue_value;}

    return draw_col;
		
}

void Renderer::drawWireFrameTriangle2d(Triangle this_triangle)
{
	SDL_Color col = this_triangle.getColor();
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
	Vec2d vert1, vert2, vert3;
	vert1 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(0).getX(), this_triangle.getTrianglePoint(0).getY()));
	vert2 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(1).getX(), this_triangle.getTrianglePoint(1).getY()));
	vert3 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(2).getX(), this_triangle.getTrianglePoint(2).getY()));
	SDL_RenderDrawLineF(renderer, vert1.getX(), vert1.getY(), vert2.getX(), vert2.getY());
	SDL_RenderDrawLineF(renderer, vert2.getX(), vert2.getY(), vert3.getX(), vert3.getY());
	SDL_RenderDrawLineF(renderer, vert3.getX(), vert3.getY(), vert1.getX(), vert1.getY());
}

void Renderer::drawFilledTriangle2d(Triangle this_triangle){
	SDL_Color col = this_triangle.getColor();
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
    
	//convert triangle x and y coords to pixel screen coords
	Vec2d vert1, vert2, vert3;
	vert1 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(0).getX(), this_triangle.getTrianglePoint(0).getY()));
	vert2 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(1).getX(), this_triangle.getTrianglePoint(1).getY()));
	vert3 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(2).getX(), this_triangle.getTrianglePoint(2).getY()));

	
	Triangle screenTri(Vec3d(vert1.getX(),vert1.getY(),this_triangle.getTrianglePoint(0).getZ(),this_triangle.getTrianglePoint(0).getW()), 
						Vec3d(vert2.getX(),vert2.getY(),this_triangle.getTrianglePoint(1).getZ(),this_triangle.getTrianglePoint(0).getW()),
						Vec3d(vert3.getX(),vert3.getY(),this_triangle.getTrianglePoint(2).getZ(),this_triangle.getTrianglePoint(0).getW()),
						this_triangle.getUVPoint(0), this_triangle.getUVPoint(1), this_triangle.getUVPoint(2), 
						this_triangle.getID(),col, this_triangle.getTexture());
						

	//rasterize triangle In Out - very slow method, implemented only for learning purposes
	//std::shared_ptr<ITriangleRasterizer> this_inout_rasterizer(new InOutRasterizer(renderer));
	//this_inout_rasterizer->drawTriangle(screenTri);

	//rasterie triangle with ScanLines - faster
	//std::shared_ptr<ITriangleRasterizer> this_scanline_rasterizer(new ScanlineRasterizer(renderer));
	//this_scanline_rasterizer->drawTriangle(screenTri);

	// Here goes TextureMapping!
	std::shared_ptr<ITriangleRasterizer> this_texturemap_rasterizer(new TexturemapRasterizer(renderer));
	this_texturemap_rasterizer->drawTriangle(screenTri);

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
	tri.setUnitNormalFromPoints();
	Vec3d normal_vector = tri.getUnitNormalVector();
	

	// perform dot product here and test <0 
	Vec3d camera_to_triangle_vector = TriPoint0-player_camera->getCameraPos();
	VectorMathService::getUnitVector(camera_to_triangle_vector);
	if (VectorMathService::dotProduct(normal_vector, camera_to_triangle_vector)<0.0f){ // Checks to see if normal vector >= 90 degs away from camera to triangle view vector
		
		// Project worldspace to Camera view
		triView.setTrianglePoint(0, VectorMathService::MultiplyMatrixVector(matView, TriPoint0));
		triView.setTrianglePoint(1, VectorMathService::MultiplyMatrixVector(matView, TriPoint1));
		triView.setTrianglePoint(2, VectorMathService::MultiplyMatrixVector(matView, TriPoint2));
		
		// Generate triangle normal in view space
		triView.setUnitNormalFromPoints();
		Vec3d view_normal_vector = triView.getUnitNormalVector();
			
		// Copy UV coordinates over
		triView.setUVPoint(0,tri.getUVPoint(0));
		triView.setUVPoint(1,tri.getUVPoint(1));
		triView.setUVPoint(2,tri.getUVPoint(2));

		// Copy Triangle ID over
		triView.setID(tri.getID());

		// Copy Texture_ptr over
		triView.setTexture(tri.getTexture());

		// Light triangle from camera 
		//Vec3d light_source_direction = Vec3d(0.0f,0.0f,1.0f); // lit like the sun
		Vec3d light_source_direction = camera_to_triangle_vector;  // omnidirectional liht out from camera position
		Vec3d light_source_normal_direction = light_source_direction*-1;
		
		
		VectorMathService::getUnitVector(light_source_normal_direction);
		float dp_light_source = VectorMathService::dotProduct(light_source_normal_direction, view_normal_vector);
		
		if(dp_light_source<0.0f) {dp_light_source=0.0f;}
		if(dp_light_source>1.0f) {dp_light_source=1.0f;}
		dp_light_source = nonVectorMathService::lerp(0.25f, 0.60f, dp_light_source); // make it so the walls aren't too shiny
		SDL_Color col; col.r=255*dp_light_source; col.g=255*dp_light_source; col.b=255*dp_light_source; col.a = 255;
		triView.setColor(col);
		//triView.setID(tri.getID());
		/*if (keyboardbreak==true){ 
			std::cout << dp_light_source << view_normal_vector.toString() << std::endl;
			keyboardbreak=false;
		}*/
		// Clip this triangle against Front, left, top, right, and bottom frustum planes, then create new triangles as necessary that end at the frustum
		std::vector<Triangle> clipped_tris = this->thisFrustumClipper->getClippedTrisAgainstFrustum(triView);

		//Project 3d triangles to 2d screen space with camera space Z information
		for(Triangle this_tri:clipped_tris)
		{
			
			Vec3d newTriPoint0 = this_tri.getTrianglePoint(0);
			Vec3d newTriPoint1 = this_tri.getTrianglePoint(1);
			Vec3d newTriPoint2 = this_tri.getTrianglePoint(2);

			pt0 = VectorMathService::MultiplyMatrixVector(matProj, newTriPoint0);
			pt1 = VectorMathService::MultiplyMatrixVector(matProj, newTriPoint1);
			pt2 = VectorMathService::MultiplyMatrixVector(matProj, newTriPoint2);
			pt0 = pt0/pt0.getW();
			pt1 = pt1/pt1.getW();
			pt2 = pt2/pt2.getW();

			

			// superimpose world Z coords from View Plane into projected space where Z isn't used anymore
			// This helps with z-lighting and z-ordering of triangles
			pt0.setZ(newTriPoint0.getZ());
			pt1.setZ(newTriPoint1.getZ());
			pt2.setZ(newTriPoint2.getZ());
			
			//pt0.setW(1/(newTriPoint0.getZ()));
			//pt1.setW(1/(newTriPoint1.getZ()));
			//pt2.setW(1/(newTriPoint2.getZ()));

			triProjected.setTrianglePoint(0,pt0);
			triProjected.setTrianglePoint(1,pt1);
			triProjected.setTrianglePoint(2,pt2);

			
		
			// Dim Lighting by Distance
			if (this->colorFrustumClippedTris==true){
				triProjected.setColor(this_tri.getColor());
				triView.setColor(this_tri.getColor());
			}else{
				triProjected.setColor(triView.getColor());
			}


			
			// Copy UV coordinates over and places them in 1/z space for perspective correction.  We will bring them out just before sampling texture
			triProjected.setUVPoint(0,Vec2d{this_tri.getUVPoint(0).getX()/pt0.getZ(),this_tri.getUVPoint(0).getY()/pt0.getZ(),1/pt0.getZ()});
			triProjected.setUVPoint(1,Vec2d{this_tri.getUVPoint(1).getX()/pt1.getZ(),this_tri.getUVPoint(1).getY()/pt1.getZ(),1/pt1.getZ()});
			triProjected.setUVPoint(2,Vec2d{this_tri.getUVPoint(2).getX()/pt2.getZ(),this_tri.getUVPoint(2).getY()/pt2.getZ(),1/pt2.getZ()});


			// Copy Triangle ID over
			triProjected.setID(tri.getID());
			
			//Copy Texture Over
			triProjected.setTexture(tri.getTexture());

			SDL_Color dimmed_col = applyDepthDimmer(triView);
			triProjected.setColor(dimmed_col);

			this->trianglesToRasterize.push_back(triProjected);
		}
	}
}

void Renderer::setColorFrustumClippedTris(bool value){
	this->colorFrustumClippedTris=value;
}

void Renderer::refreshScreen(std::shared_ptr<TrianglePipeline> my_pre_renderer){
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);	

	// start with empty triangle buffer to rasterize each frame
	this->trianglesToRasterize.clear();

	//Calculate Camera position/direction into scene
	this->matView = player_camera->buildViewMatrix();
	
	// Clip and Project Triangles to 2d screen space
	for (auto tri: my_pre_renderer->getTrianglePipeline()){ projectTriangle3d(tri); }

	// Z-order triangles so that farthest are drawn first
	my_pre_renderer->setPipelineFromTriangles(this->trianglesToRasterize);
	my_pre_renderer->orderPipelineByZ();

	// Rasterize triangles to virtual page
	this->trianglesToRasterize = my_pre_renderer->getTrianglePipeline();
	for (auto tri: this->trianglesToRasterize)
	{
		drawFilledTriangle2d(tri);
		//drawWireFrameTriangle2d(tri);
		
	}	
	
	drawReticle();

	// Flip video page to screen
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
void Renderer::cartesianToScreen_inplace(Vec2d& this_point)
{
	float HALF_SCREEN_W = (SCREEN_W)/2;
	float scaled_x = this_point.getX()*(HALF_SCREEN_W);
	this_point.setX(scaled_x+(HALF_SCREEN_W));

	float HALF_SCREEN_H = (SCREEN_H)/2;
	float scaled_y = this_point.getY()*(HALF_SCREEN_H);
	this_point.setY(SCREEN_H-(scaled_y+(HALF_SCREEN_H)));
} 


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
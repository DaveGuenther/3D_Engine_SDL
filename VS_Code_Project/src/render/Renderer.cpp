#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <iostream>

#include "../utility/Vec2d.h"
#include "../utility/Triangle.h"
#include "../utility/Mesh_Pipeline.h"
#include "../utility/Vector_Math_Service.h"
#include "../utility/nonVector_Math_Service.h"
#include "../utility/Mat4x4.h"
#include "../render/Renderer.h"
#include "../render/SDLTextureBlit.h"
#include "../render/Rasterizer.h"
#include "../render/Clipper.h"
#include "../render/Frustum.h"
#include "../render/AspectRatio.h"
#include "../render/SDLTextureBlit.h"
#include "../render/Renderer_Observer.h"
#include "../render/Font.h"
#include "../3rd_party/bitmap_font.h"
#include "../globals.h"


const float PI_by_180 = 3.14159265/180.0;

Renderer::Renderer(uint32_t SCREEN_W, uint32_t SCREEN_H, uint32_t WINDOW_W, uint32_t WINDOW_H, std::shared_ptr<Camera> player_camera, float FOV, std::shared_ptr<Frame_Rate_Manager> my_framerate, ConsoleData* console_data) {
    // SDL and Screen initializing
	this->rendererData.SCREEN_W = SCREEN_W;
    this->rendererData.SCREEN_H = SCREEN_H;
	this->rendererData.HALF_SCREEN_W = SCREEN_W/2;
	this->rendererData.HALF_SCREEN_H = SCREEN_H/2;
	this->rendererData.WINDOW_W = WINDOW_W;
    this->rendererData.WINDOW_H = WINDOW_H;
	this->rendererData.HALF_WINDOW_W = WINDOW_W/2;
	this->rendererData.HALF_WINDOW_H = WINDOW_H/2;
	this->rendererData.window_mode=SDL_WINDOW_FULLSCREEN_DESKTOP;  // 0 for Windowed, 1 for Fullscreen ((Use SDL_WINDOW_FULLSCREEN_DESKTOP)) 128 for full screen maximized, SDL_WINDOW_RESIZABLE


	this->rendererData.fFOV=FOV;
	this->rendererData.fAspectRatio = AspectRatio::getAspectRatio(SCREEN_W, SCREEN_H);
	this->rendererData.fFOV_rad = 1.0/(SDL_tanf((this->rendererData.fFOV/2)*(PI_by_180)));
    this->rendererData.windowRect.x=0;
	this->rendererData.windowRect.y=0;
	this->rendererData.windowRect.w=this->rendererData.WINDOW_W;
	this->rendererData.windowRect.h=this->rendererData.WINDOW_H;



	this->rendererData.window = SDL_CreateWindow("3D Engine", this->rendererData.HALF_WINDOW_W, this->rendererData.HALF_WINDOW_H, this->rendererData.WINDOW_W, this->rendererData.WINDOW_H, this->rendererData.window_mode);
	this->rendererData.renderer = SDL_CreateRenderer(this->rendererData.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	this->VariableFrameRate = my_framerate;

	std::shared_ptr<RendererSubject> rendererSubject(new RendererSubject(rendererData.renderer));
	this->rendererSubject=rendererSubject;

	std::shared_ptr<Renderer_Observer> rendererObserver(new Renderer_Observer(*rendererSubject));
    this->rendererObserver=rendererObserver;


	this->consoleData = console_data;
	// Show display mode information
	static int display_in_use = 0;
	int i, display_mode_count;
	SDL_DisplayMode mode;
	Uint32 f;
	display_mode_count = SDL_GetNumDisplayModes(display_in_use);
	for (i = 0; i < display_mode_count; ++i) {
		SDL_GetDisplayMode(display_in_use, i, &mode);
		f = mode.format;
		std::cout << "Display mode: " << i << "   BPP: " << SDL_BITSPERPIXEL(f) << " "<< SDL_GetPixelFormatName(f) << " Res: " << mode.w << "x" << mode.h << std::endl;
	}
	
	std::shared_ptr<Font> bitmapFont(new Font(this->rendererSubject,"Fonts/stone_term.png", "Fonts/stone_term.csv",50));
    this->bitmapFont=bitmapFont;
    this->gameFont=bitmapFont->getBitmapFontPtr();

	/*mode.h=this->SCREEN_H;
	mode.w=this->SCREEN_W;
	if(SDL_SetWindowDisplayMode(window, &mode)!=0){
		std::cout << "Cannot set display mode" << std::endl;
	}*/
	//SDL_DestroyRenderer(rendererData.renderer);
	int win_h; 
	int win_w;
	
	//SDL_SetWindowSize(rendererData.window, rendererData.WINDOW_W, rendererData.WINDOW_H);
	
	//SDL_SetWindowFullscreen( rendererData.window, SDL_WINDOW_FULLSCREEN_DESKTOP );
	//rendererData.renderer = SDL_CreateRenderer(rendererData.window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
/*	SDL_RenderSetLogicalSize(renderer, SCREEN_W, SCREEN_H);
	
*/
	SDL_GetWindowSize(this->rendererData.window, &win_w, &win_h);

	std::cout << "Window Fullscreen Size: " << win_w << win_h << std::endl;
    this->rendererData.textureBlit = new SDL_Texture_Blit(this->rendererData.renderer, this->rendererData.SCREEN_W, this->rendererData.SCREEN_H, this->rendererData.WINDOW_W, this->rendererData.WINDOW_H, this->consoleData);
	


	// Projection Matrix
	fNear = 0.1f;
	fFar = 500.0f;
	
	matProj = Mat4x4::matrixMakeProjection(this->rendererData.fFOV_rad, SCREEN_W, SCREEN_H, fNear, fFar);
	this->max_visible_z_depth = player_camera->getMaxDrawDist();
	this->inv_max_visible_z_depth = 1/this->max_visible_z_depth;  

	SDL_SetRenderDrawColor(this->rendererData.renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->rendererData.renderer);
	//SDL_WarpMouseInWindow(this->window, SCREEN_W/2, SCREEN_H/2);  //comment this out whem debugging

	this->player_camera = player_camera;
	std::shared_ptr<Clipper> thisFrustumClipper(new Clipper(player_camera, this->rendererData.fFOV));
	this->thisFrustumClipper = thisFrustumClipper;

	this->min_blue_value = 255*this->min_visible_color_modifier;
	this->min_red_value = 255*this->min_visible_color_modifier;
	this->min_green_value = 255*this->min_visible_color_modifier;

}

void Renderer::setWindowTitle(std::string title){
	char* c = const_cast<char*>(title.c_str());
	SDL_SetWindowTitle(this->rendererData.window, c);
}

void Renderer::resetMouseXY(){
	SDL_WarpMouseInWindow(this->rendererData.window, this->rendererData.HALF_SCREEN_W, this->rendererData.HALF_SCREEN_H);
}

std::shared_ptr<RendererSubject> Renderer::getRendererSubject(){
	return this->rendererSubject;
}

BitmapFont* Renderer::getBitmapFontPtr(){
	return this->gameFont;
}

SDL_Color Renderer::applyDepthDimmer(Triangle& this_tri){
    float z_center = this_tri.getTriangleZCenter();
	SDL_Color col = this_tri.getColor();
    float color_modifier;
    if (z_center>=this->max_visible_z_depth){
        color_modifier = this->min_visible_color_modifier;
    }else{
        color_modifier = 1-(z_center*this->inv_max_visible_z_depth);
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

float Renderer::applyDepthDimmerModifier(Triangle& this_tri){
    float z_center = this_tri.getTriangleZCenter();
	SDL_Color col = this_tri.getColor();
    float color_modifier;
    if (z_center>=this->max_visible_z_depth){
        color_modifier = this->min_visible_color_modifier;
    }else{
        color_modifier = 1-(z_center*this->inv_max_visible_z_depth);
		if (color_modifier<min_visible_color_modifier) { color_modifier=min_visible_color_modifier; }
    }

    return color_modifier;
		
}


void Renderer::drawWireFrameTriangle2d(Triangle this_triangle)
{
	//SDL_Color col = this_triangle.getColor();
	SDL_Color col;
	col.r=255;
	col.g=255;
	col.b=255;
	//SDL_SetRenderDrawColor(this->rendererData.renderer, col.r, col.g, col.b, col.a);
	Vec2d vert1, vert2, vert3;
	vert1 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(0).x, this_triangle.getTrianglePoint(0).y));
	vert2 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(1).x, this_triangle.getTrianglePoint(1).y));
	vert3 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(2).x, this_triangle.getTrianglePoint(2).y));
	this->rendererData.textureBlit->blitLine(vert1.x, vert1.y, vert2.x, vert2.y, col);
	this->rendererData.textureBlit->blitLine(vert2.x, vert2.y, vert3.x, vert3.y, col);
	this->rendererData.textureBlit->blitLine(vert3.x, vert3.y, vert1.x, vert1.y, col);
	
	//SDL_RenderDrawLineF(this->rendererData.renderer, vert1.x, vert1.y, vert2.x, vert2.y);
	//SDL_RenderDrawLineF(this->rendererData.renderer, vert2.x, vert2.y, vert3.x, vert3.y);
	//SDL_RenderDrawLineF(this->rendererData.renderer, vert3.x, vert3.y, vert1.x, vert1.y);
}

void Renderer::drawFilledTriangle2d(Triangle this_triangle){
	SDL_Color col = this_triangle.getColor();
	SDL_SetRenderDrawColor(this->rendererData.renderer, col.r, col.g, col.b, col.a);
    
	//convert triangle x and y coords to pixel screen coords
	Vec2d vert1, vert2, vert3;
	vert1 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(0).x, this_triangle.getTrianglePoint(0).y));
	vert2 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(1).x, this_triangle.getTrianglePoint(1).y));
	vert3 = cartesianToScreen(Vec2d(this_triangle.getTrianglePoint(2).x, this_triangle.getTrianglePoint(2).y));

	
	Triangle screenTri(Vec3d(vert1.x,vert1.y,this_triangle.getTrianglePoint(0).z,this_triangle.getTrianglePoint(0).w), 
						Vec3d(vert2.x,vert2.y,this_triangle.getTrianglePoint(1).z,this_triangle.getTrianglePoint(0).w),
						Vec3d(vert3.x,vert3.y,this_triangle.getTrianglePoint(2).z,this_triangle.getTrianglePoint(0).w),
						this_triangle.getUVPoint(0), this_triangle.getUVPoint(1), this_triangle.getUVPoint(2), 
						this_triangle.getID(),col, this_triangle.getLightDimAmount(), this_triangle.getTexture());
						


	screenTri.setLightDimAmount(this_triangle.getLightDimAmount());	


	//rasterize triangle with ScanLines - faster
	//std::shared_ptr<ITriangleRasterizer> this_scanline_rasterizer(new ScanlineRasterizer(renderer, framebufferpixels));
	//this_scanline_rasterizer->drawTriangle(screenTri);

	
	// Here goes TextureMapping!
	std::shared_ptr<ITriangleRasterizer> this_texturemap_rasterizer(new TexturemapRasterizer(this->rendererData.renderer, this->rendererData.textureBlit));
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
		// THIS CODE RUNS only for Triangles that are facing the camera

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

		// Clip this triangle against Front, left, top, right, and bottom frustum planes, then create new triangles as necessary that end at the frustum
		std::vector<Triangle> clipped_tris = this->thisFrustumClipper->getClippedTrisAgainstFrustum(triView);
		

		// Light triangle from camera 
		//Vec3d light_source_direction = Vec3d(0.0f,0.0f,1.0f); // lit like the sun
		Vec3d light_source_direction = camera_to_triangle_vector;  // omnidirectional liht out from camera position
		Vec3d light_source_normal_direction = light_source_direction*-1;
		
		
		VectorMathService::getUnitVector(light_source_normal_direction);
		float dp_light_source = VectorMathService::dotProduct(light_source_normal_direction, view_normal_vector);
		
		if(dp_light_source<0.0f) {dp_light_source=0.0f;}
		if(dp_light_source>1.0f) {dp_light_source=1.0f;}
		//dp_light_source = nonVectorMathService::lerp(0.25f, 0.75f, dp_light_source); // make it so the walls aren't too shiny
		dp_light_source = 0.7f;
		SDL_Color col; col.r=255*dp_light_source; col.g=255*dp_light_source; col.b=255*dp_light_source; col.a = 255;
		triView.setColor(col);



		//Project 3d triangles to 2d screen space with camera space Z information
		for(Triangle this_tri:clipped_tris)
		{
			
			Vec3d newTriPoint0 = this_tri.getTrianglePoint(0);
			Vec3d newTriPoint1 = this_tri.getTrianglePoint(1);
			Vec3d newTriPoint2 = this_tri.getTrianglePoint(2);

			pt0 = VectorMathService::MultiplyMatrixVector(matProj, newTriPoint0);
			pt1 = VectorMathService::MultiplyMatrixVector(matProj, newTriPoint1);
			pt2 = VectorMathService::MultiplyMatrixVector(matProj, newTriPoint2);
			pt0 = pt0/pt0.w;
			pt1 = pt1/pt1.w;
			pt2 = pt2/pt2.w;

			

			// superimpose world Z coords from View Plane into projected space where Z isn't used anymore
			// This helps with z-lighting and z-ordering of triangles
			pt0.z=newTriPoint0.z;
			pt1.z=newTriPoint1.z;
			pt2.z=newTriPoint2.z;



			triProjected.setTrianglePoint(0,pt0);
			triProjected.setTrianglePoint(1,pt1);
			triProjected.setTrianglePoint(2,pt2);

			
		
			// Dim Lighting by Distance
			if (this->colorFrustumClippedTris==true){
				//Adds RGB colors to frustrum clipped triangles
				triProjected.setColor(this_tri.getColor());
				triView.setColor(this_tri.getColor());
			}else{
				triProjected.setColor(triView.getColor());
			}

			
			float inv_pt0_z = 1/pt0.z;
			float inv_pt1_z = 1/pt1.z;
			float inv_pt2_z = 1/pt2.z;

			
			// Copy UV coordinates over and places them in 1/z space for perspective correction.  We will bring them out just before sampling texture
			triProjected.setUVPoint(0,Vec2d{this_tri.getUVPoint(0).x*inv_pt0_z,this_tri.getUVPoint(0).y*inv_pt0_z,inv_pt0_z});
			triProjected.setUVPoint(1,Vec2d{this_tri.getUVPoint(1).x*inv_pt1_z,this_tri.getUVPoint(1).y*inv_pt1_z,inv_pt1_z});
			triProjected.setUVPoint(2,Vec2d{this_tri.getUVPoint(2).x*inv_pt2_z,this_tri.getUVPoint(2).y*inv_pt2_z,inv_pt2_z});


			// Copy Triangle ID over
			triProjected.setID(tri.getID());
			
			//Copy Texture Over
			triProjected.setTexture(tri.getTexture());

			float dimmed_modifier = applyDepthDimmerModifier(triView);
			triProjected.setLightDimAmount(dimmed_modifier*dp_light_source);

			/*if ((triProjected.getID()==0)){ 
				std::cout << "Dim modifier: " << dimmed_modifier << "  Light_source_mod: " << dp_light_source << "  Total light Mod: " << triProjected.getLightDimAmount()<< std::endl;
				//std::cout << "UVx: " << UVx_scan << "    UVy: " << UVy_scan << "    col: (" << col.r << "," << col.g << "," << col.b << ")" << std::endl;
				keyboardbreak=false;   
    		}*/

			//SDL_Color dimmed_col = applyDepthDimmer(triView);
			//triProjected.setColor(dimmed_col);

			this->trianglesToRasterize.push_back(triProjected);
		}
	}
}

void Renderer::setColorFrustumClippedTris(bool value){
	this->colorFrustumClippedTris=value;
}

void Renderer::refreshScreen(std::shared_ptr<TrianglePipeline> my_pre_renderer){
	
	SDL_SetRenderDrawColor(this->rendererData.renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->rendererData.renderer);	
	
	this->rendererData.textureBlit->lock(); // prepare framebuffer for write only operation

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
		if (consoleData->rasterizer.drawPolyEdges){ drawWireFrameTriangle2d(tri); }
		
		
	}
	this->rendererData.textureBlit->unlock(); // pixel write complete, ready to render

	
	this->rendererData.textureBlit->RenderCopy();
	//SDL_Texture *this_tex = this->textureBlit->getFrameBuffer();
	//SDL_RenderCopy(renderer, this_tex, NULL, NULL); // Copy texture pixel buffer to renderer
	
	//drawReticle();
	std::string this_FPS = "FPS: "+ std::to_string(int(VariableFrameRate->getMeasuredFPS()));
	this->gameFont->placeStringAtXY(this_FPS ,10, 10, 30);

	// Flip video page to screen
	SDL_RenderPresent(this->rendererData.renderer);

} 

void Renderer::drawReticle(){
	SDL_SetRenderDrawColor(this->rendererData.renderer, 255, 255, 255, 255);
	
	// Draw Reticle
	Vec2d single_point;
	single_point.x=0;
	single_point.y=0;
	single_point = cartesianToScreen(single_point);

	float x = single_point.x;
	float y = single_point.y;
	SDL_RenderDrawPointF(this->rendererData.renderer, x, y);
}



//Private Methods
void Renderer::cartesianToScreen_inplace(Vec2d& this_point)
{
	float HALF_SCREEN_W = (this->rendererData.SCREEN_W)/2;
	float scaled_x = this_point.x*(HALF_SCREEN_W);
	this_point.x=scaled_x+(HALF_SCREEN_W);

	float HALF_SCREEN_H = (this->rendererData.SCREEN_H)/2;
	float scaled_y = this_point.y*(HALF_SCREEN_H);
	this_point.y=this->rendererData.SCREEN_H-(scaled_y+(HALF_SCREEN_H));
} 


Vec2d Renderer::cartesianToScreen(Vec2d this_point)
{
	//float HALF_SCREEN_W = (SCREEN_W)*.5;
	float scaled_x = this_point.x*(this->rendererData.HALF_SCREEN_W);
	this_point.x=scaled_x+(this->rendererData.HALF_SCREEN_W);

	//float HALF_SCREEN_H = (SCREEN_H)*.5;
	float scaled_y = this_point.y*(this->rendererData.HALF_SCREEN_H);
	this_point.y=this->rendererData.SCREEN_H-(scaled_y+(this->rendererData.HALF_SCREEN_H));
	return this_point;
} 


const int Renderer::getWindowWidth()const { return this->rendererData.SCREEN_W; }
const int Renderer::getWindowHeight()const { return this->rendererData.SCREEN_H; }

void Renderer::shutdown(){
	delete(this->rendererData.textureBlit);
	this->rendererData.textureBlit=NULL;
	SDL_DestroyRenderer(this->rendererData.renderer);
	SDL_DestroyWindow(this->rendererData.window);
	
}

Renderer::~Renderer(){

}
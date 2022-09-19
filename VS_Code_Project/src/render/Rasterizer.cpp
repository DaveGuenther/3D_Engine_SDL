
#include "Rasterizer.h"
#include <iostream>
#include <math.h>
#include "../materials/TextureList.h"
#include "../materials/TexturePNG.h"
#include "../globals.h"

void ITriangleRasterizer::applyDepthDimmer(Triangle& this_tri, SDL_Color &col){
    float z_center = this_tri.getTriangleZCenter();
    float color_modifier;
    if (z_center>=this->max_visible_z_depth){
        color_modifier = this->min_visible_color_modifier;
    }else{
        color_modifier = 1-(z_center/this->max_visible_z_depth);
    }
    SDL_Color draw_col;
    draw_col.r= col.r*color_modifier;
    draw_col.g= col.g*color_modifier;
    draw_col.b= col.b*color_modifier;
    draw_col.a=255;
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_SetRenderDrawColor(this->renderer, draw_col.r, draw_col.g, draw_col.b, SDL_ALPHA_OPAQUE);
}

TexturemapRasterizer::TexturemapRasterizer(SDL_Renderer* my_renderer){
    this->renderer=my_renderer;

}


void TexturemapRasterizer::drawTriangle(Triangle& this_triangle){

    SDL_Color col;
    // get points of triangle
    Vec3d p0 = this_triangle.getTrianglePoint(0);
    Vec3d p1 = this_triangle.getTrianglePoint(1);
    Vec3d p2 = this_triangle.getTrianglePoint(2);
    Vec2d uv_p0 = this_triangle.getUVPoint(0);
    Vec2d uv_p1 = this_triangle.getUVPoint(1);
    Vec2d uv_p2 = this_triangle.getUVPoint(2);

    p0 = p0.toThousandths();
    p1 = p1.toThousandths();
    p2 = p2.toThousandths();
    

    //applyDepthDimmer(this_triangle, col);

    // Order the points from top to bottom
    if (p0.getY() > p1.getY()) {
        Vec3d temp = p0;        p0=p1;          p1=temp; 
        Vec2d uv_temp=uv_p0;    uv_p0=uv_p1;    uv_p1=uv_temp;
    }
    if (p1.getY() > p2.getY()) {
        Vec3d temp = p1;        p1=p2;          p2=temp; 
        Vec2d uv_temp = uv_p1;  uv_p1=uv_p2;    uv_p2=uv_temp;
    }
    if (p0.getY() > p1.getY()) {
        Vec3d temp = p0;        p0=p1;          p1=temp; 
        Vec2d uv_temp = uv_p0;  uv_p0=uv_p1;    uv_p1=uv_temp;
    }


    // test for flat top
    if (p0.getY()==p1.getY()) { 
        // FLAT TOP Triangle
        if (p0.getX() > p1.getX()) {
            Vec3d temp = p0;        p0=p1;          p1=temp; 
            Vec2d uv_temp = uv_p0;  uv_p0=uv_p1;    uv_p1=uv_temp;
        }
        Triangle reordered_tri(p0, p1, p2, uv_p0, uv_p1, uv_p2,this_triangle.getID(), col, this_triangle.getLightDimAmount(), this_triangle.getTexture());
        drawFlatTopTri(reordered_tri);
        //std::cout << "Flat Top!" << std::endl;
    }

    // test for flat bottom
    else if (p1.getY()==p2.getY()) {
        if (p1.getX() > p2.getX()) {
            Vec3d temp = p1;        p1=p2;          p2=temp;
            Vec2d uv_temp = uv_p1;  uv_p1=uv_p2;    uv_p2=uv_temp;
        } 
        //FLAT BOTTOM TRIANGLE
        Triangle reordered_tri(p0, p1, p2,uv_p0, uv_p1, uv_p2,this_triangle.getID(), col, this_triangle.getLightDimAmount(), this_triangle.getTexture());
        drawFlatBottomTri(reordered_tri);
        //std::cout << "Flat Bottom" << std::endl; 
    }

    // General triangle
    else {
        float alpha = (p1.getY()-p0.getY())/(p2.getY()-p0.getY());
        

        Vec3d p_i = p0+alpha*(p2-p0);
        Vec2d uv_p_i = uv_p0+ alpha*(uv_p2-uv_p0);

        //Test for major left triangle
        if (p_i.getX()<p1.getX()){
            //MAJOR LEFT TRIANGLE 
            //std::cout << "Major Left" << std::endl; 
            Triangle flat_bottom_tri(p0, p_i, p1, uv_p0, uv_p_i, uv_p1, this_triangle.getID(), col, this_triangle.getLightDimAmount(), this_triangle.getTexture());
            Triangle flat_top_tri(p_i, p1, p2, uv_p_i, uv_p1, uv_p2, this_triangle.getID(), col, this_triangle.getLightDimAmount(), this_triangle.getTexture());
            flat_top_tri.setLightDimAmount(this_triangle.getLightDimAmount());
            flat_bottom_tri.setLightDimAmount(this_triangle.getLightDimAmount());            
            drawFlatBottomTri(flat_bottom_tri);
            drawFlatTopTri(flat_top_tri);

        }else{ 
            //MAJOR RIGHT TRIANGLE

            Triangle flat_bottom_tri(p0, p1, p_i, uv_p0, uv_p1, uv_p_i, this_triangle.getID(), col, this_triangle.getLightDimAmount(), this_triangle.getTexture());
            Triangle flat_top_tri(p1, p_i, p2, uv_p1, uv_p_i, uv_p2, this_triangle.getID(), col, this_triangle.getLightDimAmount(), this_triangle.getTexture());

            /*if (this_triangle.getID()==7){
                std::cout << "p_i=" << p_i.toString() << "uv_p_i=" << uv_p_i.toString() << std::endl;
            }*/
            flat_top_tri.setLightDimAmount(this_triangle.getLightDimAmount());
            flat_bottom_tri.setLightDimAmount(this_triangle.getLightDimAmount());
            drawFlatBottomTri(flat_bottom_tri);
            drawFlatTopTri(flat_top_tri);

            //std::cout << "Major Right" << std::endl;
        }

    }


}

void TexturemapRasterizer::drawFlatTopTri(Triangle& this_triangle){
    
    std::shared_ptr<TexturePNG> texture = this_triangle.getTexture();
    Vec3d p0 = this_triangle.getTrianglePoint(0);
    Vec2d uv0 = this_triangle.getUVPoint(0);
    Vec3d p1 = this_triangle.getTrianglePoint(1);
    Vec2d uv1 = this_triangle.getUVPoint(1);
    Vec3d p2 = this_triangle.getTrianglePoint(2);
    Vec2d uv2 = this_triangle.getUVPoint(2);


    // 1. Calculate left and right slopes using run/rise so that vertical likes aren't infinite
    float left_slope = (p2.getX()-p0.getX())/(p2.getY()-p0.getY());
    float right_slope = (p2.getX()-p1.getX())/(p2.getY()-p1.getY());


    // 2. Determine y_start and y_end pixels for the triangle
    int y_start = int(ceil(p0.getY()-0.5f));
    int y_end = int(ceil(p2.getY()-0.5f));

    // 3. Loop through each y scanline (but don't do the last one)
    for (int y = y_start;y<y_end;y++){

        // a. Calculate start and end x float points
        float p_start = left_slope * (float(y)+0.5f-p0.getY())+p0.getX();
        float p_end = right_slope * (float(y)+0.5f-p1.getY())+p1.getX();

        // b. Calculate discrete pixels for start and end x
        int x_start = int(ceil(p_start-0.5f));
        int x_end = int(ceil(p_end - 0.5f));

        //determine alpha_start (distance between v1 -> v2)
        float alpha_start = (y-p0.getY())/(p2.getY()-p0.getY());
        if (alpha_start<0.0f){alpha_start=0.0f;}
        if (alpha_start>1.0f){alpha_start=1.0f;}
        //determine alpha_end  (distance between v0 -> v2)
        float alpha_end = (y-p1.getY())/(p2.getY()-p1.getY());
        if (alpha_end<0.0f){alpha_end=0.0f;}
        if (alpha_end>1.0f){alpha_end=1.0f;}        

        //determine UV_start
        float UVx_start = alpha_start*(uv2.getX()-uv0.getX())+uv0.getX();
        float UVy_start = alpha_start*(uv2.getY()-uv0.getY())+uv0.getY();
        float UVz_start = alpha_start*(uv2.getW()-uv0.getW())+uv0.getW();
        //determine UV_end
        float UVx_end = alpha_end*(uv2.getX()-uv1.getX())+uv1.getX();
        float UVy_end = alpha_end*(uv2.getY()-uv1.getY())+uv1.getY();
        float UVz_end = alpha_end*(uv2.getW()-uv1.getW())+uv1.getW();

        // c. draw a line between x_start and x_end or draw pixels between them (don't include the pixed for x_end )
        //SDL_RenderDrawLine(this->renderer,x_start,y,x_end-1,y);
        for (int x = x_start;x<x_end;x++){ 
            
            // determine alpha_scan
            float alpha_scan;
            if (x_end==x_start){
                alpha_scan=0.0f;
            } else{
                alpha_scan = (float(x)-float(x_start))/(float(x_end)-float(x_start));
            }
            
            // determine Vec2d(U,V)
            float UVx_scan = alpha_scan*(UVx_end-UVx_start)+UVx_start;  // UVx scan is in 1/z space for perspective correction
            float UVy_scan = alpha_scan*(UVy_end-UVy_start)+UVy_start;  // UVy scan is in 1/z space for perspective correction
            float UVz_scan = alpha_scan*(UVz_end-UVz_start)+UVz_start;  // UVz scan is in projected UV space because we will need it to get UVx and UVy out of 1/z space
            UVx_scan = UVx_scan/UVz_scan;  // Brings UVx out of 1/z space into projected UV space 
            UVy_scan = UVy_scan/UVz_scan;  // Brings UVy out of 1/z space into projected UV space            
            SDL_Color col={255,255,255,255};

            if (this_triangle.getTexture()!=NULL){
                // There is a texture associated with this triangle
                texture->getPixelAtUV(UVx_scan, UVy_scan, col);
            }
            // sample texture color at (U/V)
            
            col.r=col.r*this_triangle.getLightDimAmount();
            col.g=col.g*this_triangle.getLightDimAmount();
            col.b=col.b*this_triangle.getLightDimAmount();
            
            // Set Color
            SDL_SetRenderDrawColor(this->renderer, col.r, col.g, col.b, col.a);

            // draw point at (x,)
            SDL_RenderDrawPoint(this->renderer,x, y); 
        }
    }
}

void TexturemapRasterizer::drawFlatBottomTri(Triangle& this_triangle){


    std::shared_ptr<TexturePNG> texture = this_triangle.getTexture();
    Vec3d p0 = this_triangle.getTrianglePoint(0);
    Vec2d uv0 = this_triangle.getUVPoint(0);
    Vec3d p1 = this_triangle.getTrianglePoint(1);
    Vec2d uv1 = this_triangle.getUVPoint(1);
    Vec3d p2 = this_triangle.getTrianglePoint(2);
    Vec2d uv2 = this_triangle.getUVPoint(2);

    // 1. Calculate left and right slopes using run/rise so that vertical likes aren't infinite
    float left_slope = (p1.getX()-p0.getX())/(p1.getY()-p0.getY());
    float right_slope = (p2.getX()-p0.getX())/(p2.getY()-p0.getY());

    // 2. Determine y_start and y_end pixels for the triangle
    int y_start = int(ceil(p0.getY()-0.5f));
    int y_end = int(ceil(p2.getY()-0.5f));



    // 3. Loop through each y scanline (but don't do the last one)
    for (int y = y_start;y<y_end;y++){

        // a. Calculate start and end x float points
        float p_start = left_slope * (float(y)+0.5f-p0.getY())+p0.getX();
        float p_end = right_slope * (float(y)+0.5f-p0.getY())+p0.getX();

        // b. Calculate discrete pixels for start and end x
        int x_start = int(ceil(p_start-0.5f));
        int x_end = int(ceil(p_end - 0.5f));

        //determine alpha_start (distance between v1 -> v2)
        float alpha_start = (y-p0.getY())/(p1.getY()-p0.getY());
        if (alpha_start<0.0f){alpha_start=0.0f;}
        if (alpha_start>1.0f){alpha_start=1.0f;}
        //determine alpha_end  (distance between v0 -> v2)
        float alpha_end = (y-p0.getY())/(p2.getY()-p0.getY());
        if (alpha_end<0.0f){alpha_end=0.0f;}
        if (alpha_end>1.0f){alpha_end=1.0f;}        

        //determine UV_start
        float UVx_start = alpha_start*(uv1.getX()-uv0.getX())+uv0.getX();
        float UVy_start = alpha_start*(uv1.getY()-uv0.getY())+uv0.getY();
        float UVz_start = alpha_start*(uv1.getW()-uv0.getW())+uv0.getW();
        //float UVz_start = alpha_start*((1/p1.getZ())-(1/p0.getZ()))+(1/p0.getZ());
        //determine UV_end
        float UVx_end = alpha_end*(uv2.getX()-uv0.getX())+uv0.getX();
        float UVy_end = alpha_end*(uv2.getY()-uv0.getY())+uv0.getY();
        float UVz_end = alpha_end*(uv2.getW()-uv0.getW())+uv0.getW();
        //float UVz_end = alpha_end*((1/p2.getZ())-(1/p0.getZ()))+(1/p0.getZ());

        // c. draw a line between x_start and x_end or draw pixels between them (don't include the pixed for x_end )
        for (int x = x_start;x<x_end;x++){ 
            
            // determine alpha_scan
            float alpha_scan;
            if (x_end==x_start){
                alpha_scan=0.0f;
            } else{
                alpha_scan = (float(x)-float(x_start))/(float(x_end)-float(x_start));
            }
            
            // determine Vec2d(U,V)
            float UVx_scan = alpha_scan*(UVx_end-UVx_start)+UVx_start;  // UVx scan is in 1/z space for perspective correction
            float UVy_scan = alpha_scan*(UVy_end-UVy_start)+UVy_start;  // UVy scan is in 1/z space for perspective correction
            float UVz_scan = alpha_scan*(UVz_end-UVz_start)+UVz_start;  // UVz scan is in projected UV space because we will need it to get UVx and UVy out of 1/z space
            UVx_scan = UVx_scan/UVz_scan;  // Brings UVx out of 1/z space into projected UV space 
            UVy_scan = UVy_scan/UVz_scan;  // Brings UVy out of 1/z space into projected UV space
            
            // sample texture color at (U/V)
            SDL_Color col={255,255,255,255};

            if (this_triangle.getTexture()!=NULL){
                // There is a texture associated with this triangle
                texture->getPixelAtUV(UVx_scan, UVy_scan, col);
            }


         

           
            col.r=col.r*this_triangle.getLightDimAmount();
            col.g=col.g*this_triangle.getLightDimAmount();
            col.b=col.b*this_triangle.getLightDimAmount();
            // Set Color
            SDL_SetRenderDrawColor(this->renderer, col.r, col.g, col.b, col.a);

            // draw point at (x,)
            SDL_RenderDrawPoint(this->renderer,x, y); 
            
        }
        //SDL_RenderDrawLine(this->renderer,x_start,y,x_end-1,y);

    }
}



ScanlineRasterizer::ScanlineRasterizer(SDL_Renderer* my_renderer){
    this->renderer=my_renderer;

}



void ScanlineRasterizer::drawTriangle(Triangle& this_triangle){

    SDL_Color col = this_triangle.getColor();
    // get points of triangle
    Vec3d p0 = this_triangle.getTrianglePoint(0);
    Vec3d p1 = this_triangle.getTrianglePoint(1);
    Vec3d p2 = this_triangle.getTrianglePoint(2);

    p0 = p0.toThousandths();
    p1 = p1.toThousandths();
    p2 = p2.toThousandths();
    

    //applyDepthDimmer(this_triangle, col);

    // Order the points from top to bottom
    if (p0.getY() > p1.getY()) { Vec3d temp = p0; p0=p1; p1=temp; }
    if (p1.getY() > p2.getY()) { Vec3d temp = p1; p1=p2; p2=temp; }
    if (p0.getY() > p1.getY()) { Vec3d temp = p0; p0=p1; p1=temp; }



    // test for flat top
    if (p0.getY()==p1.getY()) { 
        // FLAT TOP Triangle
        if (p0.getX() > p1.getX()) { Vec3d temp = p0; p0=p1; p1=temp; }
        Triangle reordered_tri(p0, p1, p2,0, col);
        drawFlatTopTri(reordered_tri, col);
        //std::cout << "Flat Top!" << std::endl;
    }

    // test for flat bottom
    else if (p1.getY()==p2.getY()) { 
        if (p1.getX() > p2.getX()) { Vec3d temp = p1; p1=p2; p2=temp; } 
        //FLAT BOTTOM TRIANGLE
        Triangle reordered_tri(p0, p1, p2,0, col);
        drawFlatBottomTri(reordered_tri, col);
        //std::cout << "Flat Bottom" << std::endl; 
    }

    // General triangle
    else {
        float alpha = (p1.getY()-p0.getY())/(p2.getY()-p0.getY());
        Vec3d p_i = p0+alpha*(p2-p0);

        //Test for major left triangle
        if (p_i.getX()<p1.getX()){
            //MAJOR LEFT TRIANGLE 
            //std::cout << "Major Left" << std::endl; 
            Triangle flat_bottom_tri(p0, p_i, p1,0, col);
            Triangle flat_top_tri(p_i, p1, p2,0, col);
            drawFlatTopTri(flat_top_tri, col);
            drawFlatBottomTri(flat_bottom_tri, col);
        }else{ 
            //MAJOR RIGHT TRIANGLE
            Triangle flat_bottom_tri(p0, p1, p_i, 0, col);
            Triangle flat_top_tri(p1, p_i, p2, 0, col);
            drawFlatTopTri(flat_top_tri, col);
            drawFlatBottomTri(flat_bottom_tri, col);
            //std::cout << "Major Right" << std::endl;
        }

    }


}

void ScanlineRasterizer::drawFlatTopTri(Triangle& this_triangle, SDL_Color col){
    
    Vec3d p0 = this_triangle.getTrianglePoint(0);
    Vec3d p1 = this_triangle.getTrianglePoint(1);
    Vec3d p2 = this_triangle.getTrianglePoint(2);



    // 1. Calculate left and right slopes using run/rise so that vertical likes aren't infinite
    float left_slope = (p2.getX()-p0.getX())/(p2.getY()-p0.getY());
    float right_slope = (p2.getX()-p1.getX())/(p2.getY()-p1.getY());


    // 2. Determine y_start and y_end pixels for the triangle
    int y_start = int(ceil(p0.getY()-0.5f));
    int y_end = int(ceil(p2.getY()-0.5f));

    // 3. Loop through each y scanline (but don't do the last one)
    for (int y = y_start;y<y_end;y++){

        // a. Calculate start and end x float points
        float p_start = left_slope * (float(y)+0.5f-p0.getY())+p0.getX();
        float p_end = right_slope * (float(y)+0.5f-p1.getY())+p1.getX();

        // b. Calculate discrete pixels for start and end x
        int x_start = int(ceil(p_start-0.5f));
        int x_end = int(ceil(p_end - 0.5f));

        // c. draw a line between x_start and x_end or draw pixels between them (don't include the pixed for x_end )
        SDL_RenderDrawLine(this->renderer,x_start,y,x_end-1,y);
        //for (int x = x_start;x<x_end;x++){ SDL_RenderDrawPoint(this->renderer,x, y); }

    }
}

void ScanlineRasterizer::drawFlatBottomTri(Triangle& this_triangle, SDL_Color col){

    Vec3d p0 = this_triangle.getTrianglePoint(0);
    Vec3d p1 = this_triangle.getTrianglePoint(1);
    Vec3d p2 = this_triangle.getTrianglePoint(2);


    // 1. Calculate left and right slopes using run/rise so that vertical likes aren't infinite
    float left_slope = (p1.getX()-p0.getX())/(p1.getY()-p0.getY());
    float right_slope = (p2.getX()-p0.getX())/(p2.getY()-p0.getY());

    // 2. Determine y_start and y_end pixels for the triangle
    int y_start = int(ceil(p0.getY()-0.5f));
    int y_end = int(ceil(p2.getY()-0.5f));

    // 3. Loop through each y scanline (but don't do the last one)
    for (int y = y_start;y<y_end;y++){

        // a. Calculate start and end x float points
        float p_start = left_slope * (float(y)+0.5f-p0.getY())+p0.getX();
        float p_end = right_slope * (float(y)+0.5f-p0.getY())+p0.getX();

        // b. Calculate discrete pixels for start and end x
        int x_start = int(ceil(p_start-0.5f));
        int x_end = int(ceil(p_end - 0.5f));

        // c. draw a line between x_start and x_end or draw pixels between them (don't include the pixed for x_end )
        //for (int x = x_start;x<x_end;x++){ SDL_RenderDrawPoint(this->renderer,x, y); }
        SDL_RenderDrawLine(this->renderer,x_start,y,x_end-1,y);

    }
}


InOutRasterizer::InOutRasterizer(SDL_Renderer* my_renderer){
    this->renderer=my_renderer;
}

void InOutRasterizer::drawTriangle(Triangle& this_triangle){
    //applyDepthDimmer(this_triangle, col);
    SDL_Color col = this_triangle.getColor();
    bound_box_min_x = std::min(std::min(this_triangle.getTrianglePoint(0).getX(), this_triangle.getTrianglePoint(1).getX()), this_triangle.getTrianglePoint(2).getX());
    bound_box_min_y = std::min(std::min(this_triangle.getTrianglePoint(0).getY(), this_triangle.getTrianglePoint(1).getY()), this_triangle.getTrianglePoint(2).getY());
    bound_box_max_x = std::max(std::max(this_triangle.getTrianglePoint(0).getX(), this_triangle.getTrianglePoint(1).getX()), this_triangle.getTrianglePoint(2).getX());
    bound_box_max_y = std::max(std::max(this_triangle.getTrianglePoint(0).getY(), this_triangle.getTrianglePoint(1).getY()), this_triangle.getTrianglePoint(2).getY());
    v0_x = this_triangle.getTrianglePoint(0).getX();
    v0_y = this_triangle.getTrianglePoint(0).getY();
    v0_z = this_triangle.getTrianglePoint(0).getZ();
    v1_x = this_triangle.getTrianglePoint(1).getX();
    v1_y = this_triangle.getTrianglePoint(1).getY();
    v1_z = this_triangle.getTrianglePoint(1).getZ();
    v2_x = this_triangle.getTrianglePoint(2).getX();
    v2_y = this_triangle.getTrianglePoint(2).getY();
    v2_z = this_triangle.getTrianglePoint(2).getZ();

    this->width = bound_box_max_x-bound_box_min_x;
    this->height = bound_box_max_y-bound_box_min_y;


    for (int y = 0; y<=this->height;y++){
        for (int x = 0; x<=this->width;x++){
            //test each pixel in the bounding box of the triangle to see if it should be drawn (true if it should be drawn, false if it shouldn't be drawn)
            if (isPixelContainedIn2dTriangle(x,y)){ SDL_RenderDrawPointF(renderer, this->bound_box_min_x+x, this->bound_box_min_y+y); }
        }
    }
}


bool InOutRasterizer::isPixelContainedIn2dTriangle(int Px, int Py){
    int mag_v0_v1, mag_v1_v2, mag_v2_v0=0;
    Px += this->bound_box_min_x;
    Py += this->bound_box_min_y;

    mag_v0_v1 = (Px-v0_x)*(v1_y-v0_y) - (Py-v0_y)*(v1_x-v0_x);
    mag_v1_v2 = (Px-v1_x)*(v2_y-v1_y) - (Py-v1_y)*(v2_x-v1_x);
    mag_v2_v0 = (Px-v2_x)*(v0_y-v2_y) - (Py-v2_y)*(v0_x-v2_x);

    if (mag_v0_v1<=0 && mag_v1_v2<=0 && mag_v2_v0<=0) { 
        return true;
    } else { 
        return false;
    }
}

InOutRasterizer::~InOutRasterizer(){
    
}

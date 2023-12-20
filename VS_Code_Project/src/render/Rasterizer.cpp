
#include <iostream>
#include <math.h>
#include "Rasterizer.h"

#include "../render/SDLTextureBlit.h"
#include "../materials/TextureList.h"
#include "../materials/TexturePNG.h"
#include "../globals.h"

ITriangleRasterizer::~ITriangleRasterizer(){

}

void ITriangleRasterizer::applyDepthDimmer(Triangle& this_tri, SDL_Color &col){
    float z_center = this_tri.getTriangleZCenter();
    float color_modifier;
    if (z_center>=this->max_visible_z_depth){
        color_modifier = this->min_visible_color_modifier;
    }else{
        color_modifier = 1-(z_center*this->inv_max_visible_z_depth);
    }
    SDL_Color draw_col;
    draw_col.r= col.r*color_modifier;
    draw_col.g= col.g*color_modifier;
    draw_col.b= col.b*color_modifier;
    draw_col.a=255;
    //SDL_SetRenderDrawColor(this->renderer, draw_col.r, draw_col.g, draw_col.b, SDL_ALPHA_OPAQUE);
    
}

void ITriangleRasterizer::resetTexturePtr(){

}

void ITriangleRasterizer::pixelBlit(const int &r, const int &g, const int&b, const int &a){
    
}

TexturemapRasterizer::TexturemapRasterizer(SDL_Renderer* my_renderer, SDL_Texture_LineBlit* myTexBlit){
    this->renderer=my_renderer;
    this->textureBlit = myTexBlit;
    this->inv_max_visible_z_depth=1/this->max_visible_z_depth;
    this->tex_h=this->textureBlit->getTex_h();
    this->tex_w=this->textureBlit->getTex_w();
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
    if (p0.y > p1.y) {
        Vec3d temp = p0;        p0=p1;          p1=temp; 
        Vec2d uv_temp=uv_p0;    uv_p0=uv_p1;    uv_p1=uv_temp;
    }
    if (p1.y > p2.y) {
        Vec3d temp = p1;        p1=p2;          p2=temp; 
        Vec2d uv_temp = uv_p1;  uv_p1=uv_p2;    uv_p2=uv_temp;
    }
    if (p0.y > p1.y) {
        Vec3d temp = p0;        p0=p1;          p1=temp; 
        Vec2d uv_temp = uv_p0;  uv_p0=uv_p1;    uv_p1=uv_temp;
    }


    // test for flat top
    if (p0.y==p1.y) { 
        // FLAT TOP Triangle
        if (p0.x > p1.x) {
            Vec3d temp = p0;        p0=p1;          p1=temp; 
            Vec2d uv_temp = uv_p0;  uv_p0=uv_p1;    uv_p1=uv_temp;
        }
        Triangle reordered_tri(p0, p1, p2, uv_p0, uv_p1, uv_p2,this_triangle.getID(), col, this_triangle.getLightDimAmount(), this_triangle.getTexture());
        drawFlatTopTri(reordered_tri);
        //std::cout << "Flat Top!" << std::endl;
    }

    // test for flat bottom
    else if (p1.y==p2.y) {
        if (p1.x > p2.x) {
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
        float alpha = (p1.y-p0.y)/(p2.y-p0.y);
        

        Vec3d p_i = p0+alpha*(p2-p0);
        Vec2d uv_p_i = uv_p0+ alpha*(uv_p2-uv_p0);

        //Test for major left triangle
        if (p_i.x<p1.x){
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

//void TexturemapRasterizer::flatTop

void TexturemapRasterizer::drawTriangleInitializer(Triangle &this_triangle){
    //std::shared_ptr<TexturePNG> 
    this->this_texture = this_triangle.getTextureRawPtr();
    this->p0 = this_triangle.getTrianglePoint(0);
    this->uv0 = this_triangle.getUVPoint(0);
    this->p1 = this_triangle.getTrianglePoint(1);
    this->uv1 = this_triangle.getUVPoint(1);
    this->p2 = this_triangle.getTrianglePoint(2);
    this->uv2 = this_triangle.getUVPoint(2);
}

void TexturemapRasterizer::drawFT_CalcSlopes(Triangle &this_triangle){

    // 1. Calculate left and right slopes using run/rise so that vertical likes aren't infinite
    this->inv_left_slope_denom = 1/(p2.y-p0.y);
    this->inv_right_slope_demon = 1/(p2.y-p1.y);
    this->left_slope = (p2.x-p0.x)*inv_left_slope_denom;
    this->right_slope = (p2.x-p1.x)*inv_right_slope_demon;
}

void TexturemapRasterizer::scanlineCalcStartEnd(Triangle &this_triangle){

    // 2. Determine y_start and y_end pixels for the triangle
    this->y_start = int(ceil(p0.y-0.5f));
    this->y_end = int(ceil(p2.y-0.5f));
}

void TexturemapRasterizer::drawFT_Scanline_prep(Triangle &this_triangle){
    // a. Calculate start and end x float points
    this->p_start = this->left_slope * (float(this->y)+0.5f-this->p0.y)+this->p0.x;
    this->p_end = this->right_slope * (float(this->y)+0.5f-this->p1.y)+this->p1.x;

    // b. Calculate discrete pixels for start and end x
    this->x_start = int(ceil(this->p_start-0.5f));
    this->x_end = int(ceil(this->p_end - 0.5f));

    //determine alpha_start (distance between v1 -> v2)
    this->alpha_start = (this->y-this->p0.y)*this->inv_left_slope_denom;
    if (this->alpha_start<0.0f){this->alpha_start=0.0f;}
    if (this->alpha_start>1.0f){this->alpha_start=1.0f;}
    //determine alpha_end  (distance between v0 -> v2)
    this->alpha_end = (this->y-this->p1.y)*this->inv_right_slope_demon;
    if (this->alpha_end<0.0f){this->alpha_end=0.0f;}
    if (this->alpha_end>1.0f){this->alpha_end=1.0f;}        

    //determine UV_start
    this->UVx_start = this->alpha_start*(this->uv2.x-this->uv0.x)+this->uv0.x;
    this->UVy_start = this->alpha_start*(this->uv2.y-this->uv0.y)+this->uv0.y;
    this->UVz_start = this->alpha_start*(this->uv2.uv_w-this->uv0.uv_w)+this->uv0.uv_w;
    //determine UV_end
    this->UVx_end = this->alpha_end*(this->uv2.x-this->uv1.x)+this->uv1.x;
    this->UVy_end = this->alpha_end*(this->uv2.y-this->uv1.y)+this->uv1.y;
    this->UVz_end = this->alpha_end*(this->uv2.uv_w-this->uv1.uv_w)+this->uv1.uv_w;
}

void TexturemapRasterizer::texelDetermineUV(Triangle& this_triangle){
    this->UVx_scan = this->alpha_scan*(this->UVx_end-this->UVx_start)+this->UVx_start;  // UVx scan is in 1/z space for perspective correction
    this->UVy_scan = this->alpha_scan*(this->UVy_end-this->UVy_start)+this->UVy_start;  // UVy scan is in 1/z space for perspective correction
    this->inv_UVz_scan = 1/(this->alpha_scan*(this->UVz_end-this->UVz_start)+this->UVz_start);  // UVz scan is in projected UV space because we will need it to get UVx and UVy out of 1/z space
    UVx_scan = this->UVx_scan*this->inv_UVz_scan;  // Brings UVx out of 1/z space into projected UV space 
    UVy_scan = this->UVy_scan*this->inv_UVz_scan;  // Brings UVy out of 1/z space into projected UV space            
        
}

void TexturemapRasterizer::texelDimPixel(Triangle& this_triangle){
        // apply depth dimmer
    
    this->col.r=col.r*this_triangle.getLightDimAmount();
    this->col.g=col.g*this_triangle.getLightDimAmount();
    this->col.b=col.b*this_triangle.getLightDimAmount();
}



void TexturemapRasterizer::texelDrawUV_Point(){
    this->textureBlit->blitAdvance(this->col.r, this->col.g, this->col.b, this->col.a);
}

void TexturemapRasterizer::scanlineDetermineDist(){
    // determine scanline dist
    if (this->x_end!=this->x_start){
        this->inv_scanline_dist = 1/(float(this->x_end)-float(this->x_start));
    }
}

void TexturemapRasterizer::texelDetermineAlphaX(){
    // determine alpha_scan
    if (this->x_end==this->x_start){
        this->alpha_scan=0.0f;
    } else{
        this->alpha_scan = (float(this->x)-float(this->x_start))*this->inv_scanline_dist;
    }    
}


void TexturemapRasterizer::drawFlatTopTri(Triangle& this_triangle){
    
    this->drawTriangleInitializer(this_triangle);
    this->drawFT_CalcSlopes(this_triangle);
    this->scanlineCalcStartEnd(this_triangle);


    // 3. Loop through each y scanline (but don't do the last one)
    for (this->y = this->y_start; this->y < this->y_end; this->y++){ 

        this->drawFT_Scanline_prep(this_triangle); 
        
        // determine scanline dist
        scanlineDetermineDist();
        

        // Set the TextureBlit class instance to the current line for blitting
        this->textureBlit->setXY_Start(this->x_start, this->y);

        // c. draw a line between x_start and x_end or draw pixels between them (don't include the pixed for x_end )
        //SDL_RenderDrawLine(this->renderer,x_start,y,x_end-1,y);
        for (this->x = this->x_start; this->x < this->x_end; this->x++){ 

            // determine alpha_scan
            texelDetermineAlphaX();
            

                  
            // determine Vec2d(U,V)
            texelDetermineUV(this_triangle);

            // sample texture color at (U/V)
            if (this_triangle.getTextureRawPtr()!=NULL){
                // There is a texture associated with this triangle
                this->this_texture->getPixelAtSurfaceUV(this->UVx_scan, this->UVy_scan, this->col);
            }
            
            // apply depth dimmer
            texelDimPixel(this_triangle);
            
            //Draw Point
            texelDrawUV_Point();
        
        }
        
    }
}

void TexturemapRasterizer::drawFB_CalcSlopes(Triangle &this_triangle){
    // 1. Calculate left and right slopes using run/rise so that vertical likes aren't infinite
    this->inv_left_slope_denom = 1/(this->p1.y-this->p0.y);
    this->inv_right_slope_demon = 1/(this->p2.y-this->p0.y);    
    this->left_slope = (p1.x-p0.x)*this->inv_left_slope_denom;
    this->right_slope = (p2.x-p0.x)*this->inv_right_slope_demon;
}

void TexturemapRasterizer::drawFB_Scanline_prep(Triangle &this_triangle){
        // a. Calculate start and end x float points
        this->p_start = this->left_slope * (float(this->y)+0.5f-this->p0.y)+this->p0.x;
        this->p_end = this->right_slope * (float(this->y)+0.5f-this->p0.y)+this->p0.x;

        // b. Calculate discrete pixels for start and end x
        this->x_start = int(ceil(this->p_start-0.5f));
        this->x_end = int(ceil(this->p_end - 0.5f));

        //determine alpha_start (distance between v1 -> v2)
        this->alpha_start = (this->y-p0.y)*this->inv_left_slope_denom;
        if (this->alpha_start<0.0f){this->alpha_start=0.0f;}
        if (this->alpha_start>1.0f){this->alpha_start=1.0f;}
        //determine alpha_end  (distance between v0 -> v2)
        this->alpha_end = (this->y-this->p0.y)*this->inv_right_slope_demon;
        if (this->alpha_end<0.0f){this->alpha_end=0.0f;}
        if (this->alpha_end>1.0f){this->alpha_end=1.0f;}        

        //determine UV_start
        this->UVx_start = this->alpha_start*(this->uv1.x-this->uv0.x)+this->uv0.x;
        this->UVy_start = this->alpha_start*(this->uv1.y-this->uv0.y)+this->uv0.y;
        this->UVz_start = this->alpha_start*(this->uv1.uv_w-this->uv0.uv_w)+this->uv0.uv_w;
        //float UVz_start = alpha_start*((1/p1.getZ())-(1/p0.getZ()))+(1/p0.getZ());
        //determine UV_end
        this->UVx_end = this->alpha_end*(this->uv2.x-this->uv0.x)+this->uv0.x;
        this->UVy_end = this->alpha_end*(this->uv2.y-this->uv0.y)+this->uv0.y;
        this->UVz_end = this->alpha_end*(this->uv2.uv_w-this->uv0.uv_w)+this->uv0.uv_w;

}

void TexturemapRasterizer::drawFlatBottomTri(Triangle& this_triangle){


    drawTriangleInitializer(this_triangle);

    drawFB_CalcSlopes(this_triangle);

    // 2. Determine y_start and y_end pixels for the triangle
    scanlineCalcStartEnd(this_triangle);

    // 3. Loop through each y scanline (but don't do the last one)
    for (this->y = this->y_start; this->y < this->y_end; this->y++){

        drawFB_Scanline_prep(this_triangle);

        // determine scanline dist
        scanlineDetermineDist();

        // Set the TextureBlit class instance to the current line for blitting
        this->textureBlit->setXY_Start(this->x_start, this->y);

        // c. draw a line between x_start and x_end or draw pixels between them (don't include the pixed for x_end )
        //SDL_RenderDrawLine(this->renderer,x_start,y,x_end-1,y);
        for (this->x = this->x_start; this->x < this->x_end; this->x++){ 

            // determine alpha_scan
            texelDetermineAlphaX();
            
            texelDetermineUV(this_triangle);

            if (this_triangle.getTextureRawPtr()!=NULL){
                // There is a texture associated with this triangle
                this->this_texture->getPixelAtSurfaceUV(this->UVx_scan, this->UVy_scan, this->col);
            }
        
            // apply depth dimmer
            texelDimPixel(this_triangle);
            
            // Set Color
            SDL_SetRenderDrawColor(this->renderer, col.r, col.g, col.b, col.a);

            // draw point at (x,)
            //SDL_RenderDrawPoint(this->renderer,x, y); 

            //Draw Point
            texelDrawUV_Point();
            
        }
        
    }
}



ScanlineRasterizer::ScanlineRasterizer(SDL_Renderer* my_renderer){
    this->renderer=my_renderer;
    this->inv_max_visible_z_depth=1/this->max_visible_z_depth;

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
    

    applyDepthDimmer(this_triangle, col);

    // Order the points from top to bottom
    if (p0.y > p1.y) { Vec3d temp = p0; p0=p1; p1=temp; }
    if (p1.y > p2.y) { Vec3d temp = p1; p1=p2; p2=temp; }
    if (p0.y > p1.y) { Vec3d temp = p0; p0=p1; p1=temp; }



    // test for flat top
    if (p0.y==p1.y) { 
        // FLAT TOP Triangle
        if (p0.x > p1.x) { Vec3d temp = p0; p0=p1; p1=temp; }
        Triangle reordered_tri(p0, p1, p2,0, col);
        drawFlatTopTri(reordered_tri, col);
        //std::cout << "Flat Top!" << std::endl;
    }

    // test for flat bottom
    else if (p1.y==p2.y) { 
        if (p1.x > p2.x) { Vec3d temp = p1; p1=p2; p2=temp; } 
        //FLAT BOTTOM TRIANGLE
        Triangle reordered_tri(p0, p1, p2,0, col);
        drawFlatBottomTri(reordered_tri, col);
        //std::cout << "Flat Bottom" << std::endl; 
    }

    // General triangle
    else {
        float alpha = (p1.y-p0.y)/(p2.y-p0.y);
        Vec3d p_i = p0+alpha*(p2-p0);

        //Test for major left triangle
        if (p_i.x<p1.x){
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
    float left_slope = (p2.x-p0.x)/(p2.y-p0.y);
    float right_slope = (p2.x-p1.x)/(p2.y-p1.y);


    // 2. Determine y_start and y_end pixels for the triangle
    int y_start = int(ceil(p0.y-0.5f));
    int y_end = int(ceil(p2.y-0.5f));

    // 3. Loop through each y scanline (but don't do the last one)
    for (int y = y_start;y<y_end;y++){

        // a. Calculate start and end x float points
        float p_start = left_slope * (float(y)+0.5f-p0.y)+p0.x;
        float p_end = right_slope * (float(y)+0.5f-p1.y)+p1.x;

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
    float left_slope = (p1.x-p0.x)/(p1.y-p0.y);
    float right_slope = (p2.x-p0.x)/(p2.y-p0.y);

    // 2. Determine y_start and y_end pixels for the triangle
    int y_start = int(ceil(p0.y-0.5f));
    int y_end = int(ceil(p2.y-0.5f));

    // 3. Loop through each y scanline (but don't do the last one)
    for (int y = y_start;y<y_end;y++){

        // a. Calculate start and end x float points
        float p_start = left_slope * (float(y)+0.5f-p0.y)+p0.x;
        float p_end = right_slope * (float(y)+0.5f-p0.y)+p0.x;

        // b. Calculate discrete pixels for start and end x
        int x_start = int(ceil(p_start-0.5f));
        int x_end = int(ceil(p_end - 0.5f));

        // c. draw a line between x_start and x_end or draw pixels between them (don't include the pixed for x_end )
        //for (int x = x_start;x<x_end;x++){ SDL_RenderDrawPoint(this->renderer,x, y); }
        SDL_RenderDrawLine(this->renderer,x_start,y,x_end-1,y);

    }
}



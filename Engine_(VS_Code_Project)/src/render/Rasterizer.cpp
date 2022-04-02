
#include "render/Rasterizer.h"
#include <iostream>



ScanlineRasterizer::ScanlineRasterizer(SDL_Renderer* my_renderer){
    this->renderer=my_renderer;

}
void ScanlineRasterizer::drawTriangle(Triangle& this_triangle, SDL_Color col){

    // get points of triangle
    Vec3d p0 = this_triangle.getTrianglePoint(0);
    Vec3d p1 = this_triangle.getTrianglePoint(1);
    Vec3d p2 = this_triangle.getTrianglePoint(2);

    // Order the points from top to bottom
    if (p0.getY() > p1.getY()) { Vec3d temp = p0; p0=p1; p1=temp; }
    if (p1.getY() > p2.getY()) { Vec3d temp = p1; p1=p2; p2=temp; }
    if (p0.getY() > p1.getY()) { Vec3d temp = p0; p0=p1; p1=temp; }

    // test for flat top
    if (p0.getY()==p1.getY()) { std::cout << "Flat Top!" << std::endl;}

    // test for flat bottom
    else if (p1.getY()==p2.getY()) {  std::cout << "Flat Bottom" << std::endl; }

    // General triangle
    else {
        float alpha = (p1.getY()-p0.getY())/(p2.getY()-p0.getY());
        Vec3d p_i = p0+alpha*(p2-p0);

        //Test for major left triangle
        if (p_i.getX()<p1.getX()){ std::cout << "Major Left" << std::endl; }
        else{ std::cout << "Major Right" << std::endl;}

    }


}

void ScanlineRasterizer::drawFlatTopTri(Triangle& this_triangle, SDL_Color col){

}

void ScanlineRasterizer::drawFlatBottomTri(Triangle& this_triangle, SDL_Color col){

}


InOutRasterizer::InOutRasterizer(SDL_Renderer* my_renderer){
    this->renderer=my_renderer;
}

void InOutRasterizer::drawTriangle(Triangle& this_triangle, SDL_Color col){
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
            //std::cout <<  my_bitmap[x][y];
        }
        //std::cout << std::endl;
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

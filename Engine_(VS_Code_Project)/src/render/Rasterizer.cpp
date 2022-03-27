#include "render/Rasterizer.h"
#include <iostream>


Triangle_Rasterizer::Triangle_Rasterizer(Triangle& this_triangle){

    float min_x, min_y, max_x, max_y=0;

    // Create Bounding Box for triangle
    min_x = std::min(std::min(this_triangle.getTrianglePoint(0).getX(), this_triangle.getTrianglePoint(1).getX()), this_triangle.getTrianglePoint(2).getX());
    min_y = std::min(std::min(this_triangle.getTrianglePoint(0).getY(), this_triangle.getTrianglePoint(1).getY()), this_triangle.getTrianglePoint(2).getY());
    max_x = std::max(std::max(this_triangle.getTrianglePoint(0).getX(), this_triangle.getTrianglePoint(1).getX()), this_triangle.getTrianglePoint(2).getX());
    max_y = std::max(std::max(this_triangle.getTrianglePoint(0).getY(), this_triangle.getTrianglePoint(1).getY()), this_triangle.getTrianglePoint(2).getY());
    this->tri_boundary_min = Vec2d(min_x, min_y);
    this->tri_boundary_max = Vec2d(max_x, max_y);
    
    
    this->v0 = this_triangle.getTrianglePoint(0);
    this->v1 = this_triangle.getTrianglePoint(1);
    this->v2 = this_triangle.getTrianglePoint(2);    

    this->width = int(max_x)-int(min_x);
    this->height = int(max_y)-int(min_y);

    createBitmap();
    
}

bool Triangle_Rasterizer::isPixelContainedIn2dTriangle(float Px, float Py){
    //v0(P)=(P.x−v0.x)∗(V1.y−V0.y)−(P.y−V0.y)∗(V1.x−V0.x).
    //v1(P)=(P.x−V1.x)∗(V2.y−V1.y)−(P.y−V1.y)∗(V2.x−V1.x)
    //v2(P)=(P.x−V2.x)∗(V0.y−V2.y)−(P.y−V2.y)∗(V0.x−V2.x).
    float mag_v0_v1, mag_v1_v2, mag_v2_v0=0.0;
    Px += this->tri_boundary_min.getX();
    Py += this->tri_boundary_min.getY();
    float v0_x, v0_y, v1_x, v1_y, v2_x, v2_y=0;
    v0_x=v0.getX();
    v1_x=v1.getX();
    v2_x=v2.getX();
    v0_y=v0.getY();
    v1_y=v1.getY();
    v2_y=v2.getY();
    mag_v0_v1 = (Px-v0_x)*(v1_y-v0_y) - (Py-v0_y)*(v1_x-v0_x);
    mag_v1_v2 = (Px-v1_x)*(v2_y-v1_y) - (Py-v1_y)*(v2_x-v1_x);
    mag_v2_v0 = (Px-v2_x)*(v0_y-v2_y) - (Py-v2_y)*(v0_x-v2_x);

    if (mag_v0_v1<=0.0f && mag_v1_v2<=0.0f && mag_v2_v0<=0>.0f) { 
        return true;
    } else { 
        return false;
    }

}

void Triangle_Rasterizer::createBitmap(){
    for (int y = 0; y<=this->height;y++){
        for (int x = 0; x<=this->width;x++){
            //test each pixel in the bounding box of the triangle to see if it should be drawn (true if it should be drawn, false if it shouldn't be drawn)
            my_bitmap[x][y]=isPixelContainedIn2dTriangle(x,y);
            std::cout <<  my_bitmap[x][y];
        }
        std::cout << std::endl;
    }
}

const std::map<int, std::map<int, int>>& Triangle_Rasterizer::getBitmap(){
    return my_bitmap;
}

const Vec2d Triangle_Rasterizer::getBitmapStartPos(){
    return this->tri_boundary_min;
}

const Vec2d Triangle_Rasterizer::getBitmapSize(){
    return Vec2d(this->tri_boundary_max.getX()-this->tri_boundary_min.getX(), this->tri_boundary_max.getY()-this->tri_boundary_min.getY());
}
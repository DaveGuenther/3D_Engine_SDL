
#include "render/Rasterizer.h"
#include <iostream>


Triangle_Rasterizer::Triangle_Rasterizer(Triangle& this_triangle): bound_box_min_x(std::min(std::min(this_triangle.getTrianglePoint(0).getX(), this_triangle.getTrianglePoint(1).getX()), this_triangle.getTrianglePoint(2).getX())),
                                                                bound_box_min_y(std::min(std::min(this_triangle.getTrianglePoint(0).getY(), this_triangle.getTrianglePoint(1).getY()), this_triangle.getTrianglePoint(2).getY())),
                                                                bound_box_max_x(std::max(std::max(this_triangle.getTrianglePoint(0).getX(), this_triangle.getTrianglePoint(1).getX()), this_triangle.getTrianglePoint(2).getX())),
                                                                bound_box_max_y(std::max(std::max(this_triangle.getTrianglePoint(0).getY(), this_triangle.getTrianglePoint(1).getY()), this_triangle.getTrianglePoint(2).getY())),
                                                                v0_x(this_triangle.getTrianglePoint(0).getX()),
                                                                v0_y(this_triangle.getTrianglePoint(0).getY()),
                                                                v0_z(this_triangle.getTrianglePoint(0).getZ()),
                                                                v1_x(this_triangle.getTrianglePoint(1).getX()),
                                                                v1_y(this_triangle.getTrianglePoint(1).getY()),
                                                                v1_z(this_triangle.getTrianglePoint(1).getZ()),
                                                                v2_x(this_triangle.getTrianglePoint(2).getX()),
                                                                v2_y(this_triangle.getTrianglePoint(2).getY()),
                                                                v2_z(this_triangle.getTrianglePoint(2).getZ())                                                            
                                                                {

    this->width = bound_box_max_x-bound_box_min_x;
    this->height = bound_box_max_y-bound_box_min_y;

    createBitmap();
    
}

bool Triangle_Rasterizer::isPixelContainedIn2dTriangle(int Px, int Py){

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

void Triangle_Rasterizer::createBitmap(){
    std::cout << "Creating Bitmap...";
    for (int y = 0; y<=this->height;y++){
        for (int x = 0; x<=this->width;x++){
            //test each pixel in the bounding box of the triangle to see if it should be drawn (true if it should be drawn, false if it shouldn't be drawn)
            my_bitmap[x][y]=isPixelContainedIn2dTriangle(x,y);
            //std::cout <<  my_bitmap[x][y];
        }
        //std::cout << std::endl;
    }
    std::cout << "Finished" << std::endl;
}

const std::map<int, std::map<int, bool>>& Triangle_Rasterizer::getBitmap(){
    return my_bitmap;
}

const Vec2d Triangle_Rasterizer::getBitmapStartPos(){
    return Vec2d(this->bound_box_min_x, this->bound_box_min_y);
}

const Vec2d Triangle_Rasterizer::getBitmapSize(){
    return Vec2d(this->bound_box_max_x-this->bound_box_min_x, this->bound_box_max_y-this->bound_box_min_y);
}
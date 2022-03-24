#include <SDL2/SDL.h>
#include <algorithm>
#include "utility/Triangle_Modifier.h"
#include "utility/Multiply_Matrix_Service.h"

void Triangle_Modifier::assignToMesh(int mesh_id){
    mesh_ids.push_back(mesh_id);
}

const std::vector<int> Triangle_Modifier::getAssignedMeshIDs(){
    return mesh_ids;
}

void Triangle_Modifier::clearMeshAssignments(){
    this->mesh_ids.clear();
}

Rotator::Rotator(float x_degrees, float y_degrees, float z_degrees, Vec3d center){
    x_degs = x_degrees;
    y_degs = y_degrees;
    z_degs = z_degrees;
    center_of_rotation = center;

    //X Rotation MAtrix
    mat_XRot.m[0][0] = 1;
    mat_XRot.m[0][1] = 0;
    mat_XRot.m[0][2] = 0;
    mat_XRot.m[0][3] = 0;

    mat_XRot.m[1][0] = 0;
    mat_XRot.m[1][1] = SDL_cosf(x_degs*(3.14159265/180.0));
    mat_XRot.m[1][2] = SDL_sinf(x_degs*(3.14159265/180.0));
    mat_XRot.m[1][3] = 0;

    mat_XRot.m[2][0] = 0;
    mat_XRot.m[2][1] = -SDL_sinf(x_degs*(3.14159265/180.0));
    mat_XRot.m[2][2] = SDL_cosf(x_degs*(3.14159265/180.0));
    mat_XRot.m[2][3] = 0;

    mat_XRot.m[3][0] = 0;
    mat_XRot.m[3][1] = 0;
    mat_XRot.m[3][2] = 0;
    mat_XRot.m[3][3] = 1;

    //Y Rotation MAtrix
    mat_YRot.m[0][0] = SDL_cosf(y_degs*(3.14159265/180.0));
    mat_YRot.m[0][1] = 0;
    mat_YRot.m[0][2] = -SDL_sinf(y_degs*(3.14159265/180.0));
    mat_YRot.m[0][3] = 0;

    mat_YRot.m[1][0] = 0;
    mat_YRot.m[1][1] = 1;
    mat_YRot.m[1][2] = 0;
    mat_YRot.m[1][3] = 0;

    mat_YRot.m[2][0] = SDL_sinf(y_degs*(3.14159265/180.0));
    mat_YRot.m[2][1] = 0;
    mat_YRot.m[2][2] = SDL_cosf(y_degs*(3.14159265/180.0));
    mat_YRot.m[2][3] = 0;

    mat_YRot.m[3][0] = 0;
    mat_YRot.m[3][1] = 0;
    mat_YRot.m[3][2] = 0;
    mat_YRot.m[3][3] = 1;

    //Z Rotation Matrix
    mat_ZRot.m[0][0] = SDL_cosf(z_degs*(3.14159265/180.0));
    mat_ZRot.m[0][1] = SDL_sinf(z_degs*(3.14159265/180.0));
    mat_ZRot.m[0][2] = 0;
    mat_ZRot.m[0][3] = 0;

    mat_ZRot.m[1][0] = -SDL_sinf(z_degs*(3.14159265/180.0));
    mat_ZRot.m[1][1] = SDL_cosf(z_degs*(3.14159265/180.0));
    mat_ZRot.m[1][2] = 0;
    mat_ZRot.m[1][3] = 0;

    mat_ZRot.m[2][0] = 0;
    mat_ZRot.m[2][1] = 0;
    mat_ZRot.m[2][2] = 1;
    mat_ZRot.m[2][3] = 0;

    mat_ZRot.m[3][0] = 0;
    mat_ZRot.m[3][1] = 0;
    mat_ZRot.m[3][2] = 0;
    mat_ZRot.m[3][3] = 1;
    		

}



void Rotator::modifyTriangle(Triangle &tri){
    //std::cout << "Rotating Triangle" << std::endl;

    Vec3d pt1_i = tri.getTrianglePoint(0);
    Vec3d pt1_o = pt1_i;
    Vec3d pt2_i = tri.getTrianglePoint(1);
    Vec3d pt2_o = pt2_i;
    Vec3d pt3_i = tri.getTrianglePoint(2);
    Vec3d pt3_o = pt3_i;

    if (z_degs!=0){
        Multiply_Matrix_Service::MultiplyMatrixVector(pt1_i, pt1_o, mat_ZRot);
        Multiply_Matrix_Service::MultiplyMatrixVector(pt2_i, pt2_o, mat_ZRot);
        Multiply_Matrix_Service::MultiplyMatrixVector(pt3_i, pt3_o, mat_ZRot);
        pt1_i=pt1_o;
        pt2_i=pt2_o;
        pt3_i=pt3_o;
    }

     if (x_degs!=0){
        Multiply_Matrix_Service::MultiplyMatrixVector(pt1_i, pt1_o, mat_XRot);
        Multiply_Matrix_Service::MultiplyMatrixVector(pt2_i, pt2_o, mat_XRot);
        Multiply_Matrix_Service::MultiplyMatrixVector(pt3_i, pt3_o, mat_XRot);
        pt1_i=pt1_o;
        pt2_i=pt2_o;
        pt3_i=pt3_o;
    }   

     if (y_degs!=0){
        Multiply_Matrix_Service::MultiplyMatrixVector(pt1_i, pt1_o, mat_YRot);
        Multiply_Matrix_Service::MultiplyMatrixVector(pt2_i, pt2_o, mat_YRot);
        Multiply_Matrix_Service::MultiplyMatrixVector(pt3_i, pt3_o, mat_YRot);
        pt1_i=pt1_o;
        pt2_i=pt2_o;
        pt3_i=pt3_o;
    }   
    tri.setTrianglePoint(0,pt1_i);
    tri.setTrianglePoint(1,pt2_i);
    tri.setTrianglePoint(2,pt3_i);
    //std::cout << tri.toString() << std::endl;
    //std::cout << "Done Rotating Triangle" << std::endl;
}



Translator::Translator(float x_distance, float y_distance,  float z_distance){
    x_dist = x_distance;
    y_dist = y_distance;
    z_dist = z_distance;
}

void Translator::modifyTriangle(Triangle& tri){
    //std::cout << "Translating Triangle" << std::endl;

    for (int i=0;i<3;i++){
        Vec3d point = tri.getTrianglePoint(i);
        if (x_dist!=0){ point.setX(point.getX()+x_dist);}
        if (y_dist!=0){ point.setY(point.getY()+y_dist);}
        if (z_dist!=0){ point.setZ(point.getZ()+z_dist);}
        tri.setTrianglePoint(i,point);
    
    }
    //std::cout << tri.toString() << std::endl;
    //std::cout << "Done Translating Triangle" << std::endl;
}



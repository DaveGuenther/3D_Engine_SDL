#include <SDL2/SDL.h>
#include <algorithm>
#include "Triangle_Modifier.h"
#include "Vector_Math_Service.h"

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

    //X Rotation Matrix
    mat_XRot = Mat4x4::matrixMakeRotationX(x_degs);

    //Y Rotation Matrix
    mat_YRot = Mat4x4::matrixMakeRotationY(y_degs);
 
    //Z Rotation Matrix
    mat_ZRot = Mat4x4::matrixMakeRotationZ(z_degs);

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
        pt1_o = VectorMathService::MultiplyMatrixVector(mat_ZRot, pt1_i);
        pt2_o = VectorMathService::MultiplyMatrixVector(mat_ZRot, pt2_i);
        pt3_o = VectorMathService::MultiplyMatrixVector(mat_ZRot, pt3_i);
        pt1_i=pt1_o;
        pt2_i=pt2_o;
        pt3_i=pt3_o;
    }

     if (x_degs!=0){
        pt1_o = VectorMathService::MultiplyMatrixVector(mat_XRot, pt1_i);
        pt2_o = VectorMathService::MultiplyMatrixVector(mat_XRot, pt2_i);
        pt3_o = VectorMathService::MultiplyMatrixVector(mat_XRot, pt3_i);
        pt1_i=pt1_o;
        pt2_i=pt2_o;
        pt3_i=pt3_o;
    }   

     if (y_degs!=0){
        pt1_o = VectorMathService::MultiplyMatrixVector(mat_YRot, pt1_i);
        pt2_o = VectorMathService::MultiplyMatrixVector(mat_YRot, pt2_i);
        pt3_o = VectorMathService::MultiplyMatrixVector(mat_YRot, pt3_i);
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

    //Mat4x4 matTrans;
    //matTrans= Mat4x4::matrixMakeTranslation(x_dist, y_dist, z_dist);

}

void Translator::modifyTriangle(Triangle& tri){
    //std::cout << "Translating Triangle" << std::endl;

    for (int i=0;i<3;i++){
        Vec3d point = tri.getTrianglePoint(i);
        if (x_dist!=0){ point.x=point.x+x_dist;}
        if (y_dist!=0){ point.y=point.y+y_dist;}
        if (z_dist!=0){ point.setZ(point.getZ()+z_dist);}
        tri.setTrianglePoint(i,point);
    
    }
    //std::cout << tri.toString() << std::endl;
    //std::cout << "Done Translating Triangle" << std::endl;
}



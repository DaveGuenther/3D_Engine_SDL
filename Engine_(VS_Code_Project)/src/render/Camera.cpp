#include <iostream>
#include "globals.h"
#include "render/Camera.h"
#include "utility/Mat4x4.h"
#include "utility/Vector_Math_Service.h"


Camera::Camera(){
    this->camera = Vec3d(0.0f, 0.0f, 0.0f);
    this->lookVector = Vec3d(0.0f, 0.0f, 1.0f);
    this->vTarget = Vec3d(0.0f,0.0f,1.0f);
}

Mat4x4 Camera::buildViewMatrix(){
    
	Vec3d vUp=Vec3d(0.0f,1.0f,0.0f);
	Vec3d offsetTarget = calc_vTarget();
    std::cout <<"  offset vTarget: " << offsetTarget.toString() << std::endl;
	Mat4x4 matCamera = Mat4x4::matrixPointAt(this->camera, offsetTarget, vUp);

    Mat4x4 matView= Mat4x4::matrixLookAt(matCamera);
    
	return matView;
}

void Camera::rotateCamera(Vec3d rotation_vector){
    this->yaw = rotation_vector.getY(); // Amount of rotation around the Y axis (turn the camera left or right)
    this->pitch = rotation_vector.getX(); // Amount of rotation around X axis (pitch the camera up and down)
    Vec3d ForwardZ = Vec3d(0,0,1);
    /*if (keyboardbreak==true){
        std::cout << "BREAK!" << std::endl;
        yaw=160.0f;
        pitch=45.0f;
        keyboardbreak=false;
    }*/

/*
    Mat4x4 matCameraRotX = Mat4x4::matrixMakeRotationX(pitch);
    this->lookVector = VectorMathService::MultiplyMatrixVector(matCameraRotX, this->vTarget);
    this->vTarget=this->lookVector; 

   
     
    //std::cout << "  LookVectors: " << lookVector.toString() << "  old vTarget: " << vTarget.toString();
    Mat4x4 matCameraRotY = Mat4x4::matrixMakeRotationY(yaw);
    this->lookVector = VectorMathService::MultiplyMatrixVector(matCameraRotY, this->vTarget);
    this->vTarget=this->lookVector;

*/

    Mat4x4 matCameraRotX = Mat4x4::matrixMakeRotationX(pitch);
    Mat4x4 matCameraRotY = Mat4x4::matrixMakeRotationY(yaw);
    Mat4x4 matCameraRotXY = Mat4x4::matrixMatrixMultiplication(matCameraRotX, matCameraRotY);
    this->lookVector = VectorMathService::MultiplyMatrixVector(matCameraRotXY, vTarget);
    this->vTarget=this->lookVector; 


}

Vec3d Camera::calc_vTarget(){
    return (this->camera+this->lookVector);

}

void Camera::setCameraDir(Vec3d dir_vector){
    VectorMathService::getUnitVector(dir_vector);
    this->lookVector=dir_vector;
}

void Camera::setCameraPos(Vec3d transform_from_forward){

    //Forward and Backward movement
    // Determine magnitude of Forward/Backward movement in the direction that is forward to the camera, then add that vector to the camera's position
    Vec3d vForwardBackward = this->lookVector*transform_from_forward.getZ();
    vForwardBackward.setY(0.0f); // make it so you don't travel up or down by looking that direction and moving foward
    this->camera=this->camera+vForwardBackward;



    // Side-to-Side movement
    // Find the normal (left) vector of the camera's forward and up (always Vec3d(0,1,0)) vector.  
    Vec3d vLeftdir = VectorMathService::crossProduct(this->lookVector,Vec3d(0.0f,1.0f,0.0f));
    VectorMathService::getUnitVector(vLeftdir);
    // Determine magnitude of Left/Right movement in the direction that is left to the camera, then add that vector to the camera's position
    Vec3d vLeftRight = vLeftdir*transform_from_forward.getX();
    this->camera = this->camera-vLeftRight; 


    // Up Down movement
    // Apply movement directly to the camera's y value.  This is Quake, not Descent.
    this->camera.setY(this->camera.getY()+transform_from_forward.getY());

}

Vec3d Camera::getCameraPos(){
    return this->camera;
}

Vec3d Camera::getCameraDir(){
    return this->lookVector;
}
#include <iostream>
#include "render/Camera.h"
#include "utility/Mat4x4.h"
#include "utility/Vector_Math_Service.h"


Camera::Camera(){
    this->camera = Vec3d(0.0f, 0.0f, -10.0f);
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
    this->yaw = rotation_vector.getY();
    this->pitch = rotation_vector.getX();
    //this->vTarget= Vec3d(0.0f,0.0f,1.0f);
     
    std::cout << "  LookVectors: " << lookVector.toString() << "  old vTarget: " << vTarget.toString();
    Mat4x4 matCameraRotY = Mat4x4::matrixMakeRotationY(yaw);
    this->lookVector = VectorMathService::MultiplyMatrixVector(matCameraRotY, this->vTarget);
    this->vTarget=this->lookVector;

    std::cout <<lookVector.toString() << "  camera: " << this->camera.toString();

    //Mat4x4 matCameraRotX = Mat4x4::matrixMakeRotationX(rotation_vector.getX());
    //this->lookVector = VectorMathService::MultiplyMatrixVector(matCameraRotX, this->vTarget);
    //this->vTarget = calc_vTarget();


}

Vec3d Camera::calc_vTarget(){
    return (this->camera+this->lookVector);

}

void Camera::setCameraDir(Vec3d dir_vector){
    VectorMathService::getUnitVector(dir_vector);
    this->lookVector=dir_vector;
}

void Camera::setCameraPos(Vec3d transform_from_forward){
    //this->vTarget= this->vTarget+pos_vector;
    //VectorMathService::getUnitVector(vTarget);
    
    //this->camera=pos_vector;
    Vec3d vForwardBackward = this->lookVector*transform_from_forward.getZ();
    this->camera=this->camera+vForwardBackward;
    Vec3d vLeftdir = VectorMathService::crossProduct(this->lookVector,Vec3d(0.0f,1.0f,0.0f));
    VectorMathService::getUnitVector(vLeftdir);
    Vec3d vLeftRight = vLeftdir*transform_from_forward.getX();
    this->camera = this->camera-vLeftRight; 
}

Vec3d Camera::getCameraPos(){
    return this->camera;
}

Vec3d Camera::getCameraDir(){
    return this->lookVector;
}
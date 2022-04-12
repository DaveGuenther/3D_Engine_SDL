#include "render/Camera.h"
#include "utility/Mat4x4.h"


Camera::Camera(){
    this->camera = Vec3d(0.0f, 0.0f, 0.0f);
    this->lookVector = Vec3d(0.0f, 0.0f, 1.0f);
}

Mat4x4 Camera::buildViewMatrix(){
    
	Vec3d vUp=Vec3d(0.0f,1.0f,0.0f);
	Vec3d vTarget = this->camera+lookVector;

	Mat4x4 matCamera = Mat4x4::matrixPointAt(this->camera, vTarget, vUp);

    Mat4x4 matView= Mat4x4::matrixLookAt(matCamera);
    
	return matView;
}

void Camera::setCameraDir(Vec3d dir_vector){
    this->lookVector=dir_vector;
}

void Camera::setCameraPos(Vec3d pos_vector){
    this->camera=pos_vector;
}

Vec3d Camera::getCameraPos(){
    return this->camera;
}

Vec3d Camera::getCameraDir(){
    return this->lookVector;
}
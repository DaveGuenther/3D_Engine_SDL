#include <iostream>
#include "Camera.h"
#include "../utility/Mat4x4.h"
#include "../utility/Vector_Math_Service.h"
#include "Frustum.h"


Camera::Camera(float aspectRatio):camera(Vec3d(0.0f, 0.0f, 0.0f)), 
                                lookVector(Vec3d(0.0f, 0.0f, 1.0f)),
                                vTarget(Vec3d(0.0f, 0.0f, 1.0f)), 
                                cameraViewFrustum(new Frustum(aspectRatio)){
    //this->camera = Vec3d(0.0f, 0.0f, 0.0f);
    //this->lookVector = Vec3d(0.0f, 0.0f, 1.0f);
    //this->vTarget = Vec3d(0.0f,0.0f,1.0f);
}

Mat4x4 Camera::buildViewMatrix(){
    
	Vec3d vUp=Vec3d(0.0f,1.0f,0.0f);

    // update new point at vector for the camera to point at when rendering
    this->vTarget = this->calc_vTarget();

    // point the camera at the new vTarget vector from it's new position (which is just behind it)
	Mat4x4 matCamera = Mat4x4::matrixPointAt(this->camera, vTarget, vUp);

    // Invert the camera so that the world objects are rotated the opposite direction (which is actually what we want when we rotate the camera)
    Mat4x4 matView= Mat4x4::matrixLookAt(matCamera);

    // matView is used during the Renderer::refreshScreen method
	return matView;
}

/*void Camera::defineFrustumEdgePlanes(){
    Vec2d screen_left_edge = Vec2d(-1.0f, 0.0f), screen_right_edge = Vec2d(1.0f, 0.0f), screen_top_edge = Vec2d(0.0f, 1.0f), screen_bottom_edge = Vec2d(0.0f, -1.0f);
    //Vec3d frustum_top_ray = Vec3d(screen_top_edge.getX()
}*/

void Camera::rotateCamera(Vec3d rotation_vector){
    // Update total pitch and yaw
    this->yaw_total = rotation_vector.y+yaw_total; // Amount of rotation around the Y axis (turn the camera left or right)
    this->pitch_total = rotation_vector.x+pitch_total; // Amount of rotation around X axis (pitch the camera up and down)
    this->vTarget = Vec3d(0,0,1);


    // Create combined XY rotation matrix
    Mat4x4 matCameraRotX = Mat4x4::matrixMakeRotationX(pitch_total);
    Mat4x4 matCameraRotY = Mat4x4::matrixMakeRotationY(yaw_total);
    Mat4x4 matCameraRotXY = Mat4x4::matrixMatrixMultiplication(matCameraRotX, matCameraRotY);
    
    // Create a new camera direction as a unit vector starting from z-forward (0,0,1)
    this->lookVector = VectorMathService::MultiplyMatrixVector(matCameraRotXY, this->vTarget);
    
}

Vec3d Camera::calc_vTarget(){
    return (this->camera+this->lookVector);
}

void Camera::setCameraPos(Vec3d transform_from_forward){

    //Forward and Backward movement
    // Determine magnitude of Forward/Backward movement in the direction that is forward to the camera, then add that vector to the camera's position
    Vec3d vForwardBackward = this->lookVector*transform_from_forward.z;
    vForwardBackward.y=0.0f; // make it so you don't travel up or down by looking that direction and moving foward
    this->camera=this->camera+vForwardBackward;



    // Side-to-Side movement
    // Find the normal (left) vector of the camera's forward and up (always Vec3d(0,1,0)) vector.  
    Vec3d vLeftdir = VectorMathService::crossProduct(this->lookVector,Vec3d(0.0f,1.0f,0.0f));
    VectorMathService::getUnitVector(vLeftdir);
    // Determine magnitude of Left/Right movement in the direction that is left to the camera, then add that vector to the camera's position
    Vec3d vLeftRight = vLeftdir*transform_from_forward.x;
    this->camera = this->camera-vLeftRight; 


    // Up Down movement
    // Apply movement directly to the camera's y value.  This is Quake, not Descent.
    this->camera.y=this->camera.y+transform_from_forward.y;

}

Vec3d Camera::getCameraPos(){
    return this->camera;
}

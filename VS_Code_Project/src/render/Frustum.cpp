#include <SDL2/SDL.h>
#include "../render/Frustum.h"
#include "../utility/Vector_Math_Service.h"

Frustum::Frustum(float aspectRatio, float max_draw_dist, float fFOV){
    float PI_by_180 = 3.14159265/180.0;
    float FOV=90-fFOV+90;  // I have no idea why I have to have a different FOV value (inverted about 90) in order for the frustrum plane normals to be defined properly.
    float cos_FOV = SDL_cosf((FOV/2)*PI_by_180);
    float sin_FOV = SDL_sinf((FOV/2)*PI_by_180);
    /*float rad_FOV = SDL_atanf((FOV/2)*PI_by_180);
    float matProjx = aspectRatio*rad_FOV;
    float matProjy = rad_FOV;

    // calculate top frustum plane normal
    Vec3d frust_top_ray = Vec3d(0.0f/matProjx, 1.0f/matProjy, 1.0f);
    Vec3d camera_right = Vec3d(1.0f, 0.0f, 0.0f);
    Vec3d top_frust_normal = VectorMathService::crossProduct(camera_right,frust_top_ray);
    
    // calculate bottom frustum plane normal
    Vec3d frust_bottom_ray = Vec3d(0.0f/matProjx, -1.0f/matProjy, 1.0f);
    Vec3d camera_left = Vec3d(-1.0f, 0.0f, 0.0f);
    Vec3d bottom_frust_normal = VectorMathService::crossProduct(camera_left,frust_bottom_ray);

    // calculate left frustum plane normal
    Vec3d frust_left_ray = Vec3d(-1.0f/matProjx, 0.0f/matProjy, 1.0f);
    Vec3d camera_up = Vec3d(0.0f, 1.0f, 0.0f);
    Vec3d left_frust_normal = VectorMathService::crossProduct(camera_up, frust_left_ray);

    // calculate bottom frustum plane normal
    Vec3d frust_right_ray = Vec3d(1.0f/matProjx, 0.0f/matProjy, 1.0f);
    Vec3d camera_down = Vec3d(0.0f, -1.0f, 0.0f);
    Vec3d right_frust_normal = VectorMathService::crossProduct(camera_down, frust_right_ray);
*/

    float dx = sin_FOV;
    float dy = sin_FOV;
    float dz = cos_FOV;


    this->frustum_front_plane_normal = Vec3d(0.0f, 0.0f, 1.0f);
    this->frustum_front_point = Vec3d(0.0f, 0.0f, 0.1f);
    //this->frustum_left_plane_normal = Vec3d(aspectRatio, 0.0f, 1.0f);
    //this->frustum_right_plane_normal = Vec3d(-1*aspectRatio, 0.0f, 1.0f);
    //this->frustum_top_plane_normal = Vec3d(0.0f, -1.0f, 1.0f);
    //this->frustum_bottom_plane_normal = Vec3d(0.0f, 1.0f, 1.0f);

    this->frustum_left_plane_normal = Vec3d(dx*aspectRatio, 0.0f, 1.0f*dz);
    this->frustum_right_plane_normal = Vec3d(-1*dx*aspectRatio, 0.0f, 1.0f*dz);
    this->frustum_top_plane_normal = Vec3d(0.0f, -1.0f*dy, 1.0f*dz);
    this->frustum_bottom_plane_normal = Vec3d(0.0f, 1.0f*dy, 1.0f*dz);
    this->frustum_origin_point = Vec3d(0.0f, 0.0f, 0.0f);
    this->frustrum_back_plane_normal = Vec3d(0.0f, 0.0f, -1.0f);
    this->frustrum_back_point = Vec3d(0.0f, 0.0f, max_draw_dist);
}

const Vec3d& Frustum::getFrustumFrontPlaneNormal(){
    return this->frustum_front_plane_normal;
}

const Vec3d& Frustum::getFrustumFrontPoint(){
    return this->frustum_front_point;
}

const Vec3d& Frustum::getFrustumLeftPlaneNormal(){
    return this->frustum_left_plane_normal;
}

const Vec3d& Frustum::getFrustumRightPlaneNormal(){
    return this->frustum_right_plane_normal;
}

const Vec3d& Frustum::getFrustumTopPlaneNormal(){
    return this->frustum_top_plane_normal;
}

const Vec3d& Frustum::getFrustumBottomPlaneNormal(){
    return this->frustum_bottom_plane_normal;

}

const Vec3d& Frustum::getFrustumOriginPoint(){
    return this->frustum_origin_point;
}

const Vec3d& Frustum::getFrustrumBackPlaneNormal(){
    return this->frustrum_back_plane_normal;
}

const Vec3d& Frustum::getFrustrumBackPoint(){
    return this->frustrum_back_point;
}
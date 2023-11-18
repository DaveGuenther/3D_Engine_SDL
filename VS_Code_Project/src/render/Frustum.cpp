#include "../render/Frustum.h"

Frustum::Frustum(float aspectRatio, float max_draw_dist): frustum_front_plane_normal(Vec3d(0.0f, 0.0f, 1.0f)),
                                    frustum_front_point(Vec3d(0.0f, 0.0f, 0.1f)),
                                    frustum_left_plane_normal(Vec3d(aspectRatio, 0.0f, 1.0f)),
                                    frustum_right_plane_normal(Vec3d(-1*aspectRatio, 0.0f, 1.0f)),
                                    frustum_top_plane_normal(Vec3d(0.0f, -1.0f, 1.0f)),
                                    frustum_bottom_plane_normal(Vec3d(0.0f, 1.0f, 1.0f)),
                                    frustum_origin_point(Vec3d(0.0f, 0.0f, 0.0f)),
                                    frustrum_back_plane_normal(Vec3d(0.0f, 0.0f, -1.0f)),
                                    frustrum_back_point(Vec3d(0.0f, 0.0f, max_draw_dist)){
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
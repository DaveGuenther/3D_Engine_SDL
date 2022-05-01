#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "utility/Vec3d.h"

class Frustum{
    public:
        Frustum(float AspectRatio);
        //Vec3d& Frustum::getFrustumFrontPlaneNormal{
        const Vec3d& getFrustumFrontPlaneNormal();
        const Vec3d& getFrustumFrontPoint();
        const Vec3d& getFrustumLeftPlaneNormal();
        const Vec3d& getFrustumRightPlaneNormal();
        const Vec3d& getFrustumTopPlaneNormal();
        const Vec3d& getFrustumBottomPlaneNormal();
        const Vec3d& getFrustumOriginPoint();


    private: 
    Vec3d frustum_front_plane_normal;
    Vec3d frustum_front_point;

    Vec3d frustum_left_plane_normal;
    Vec3d frustum_right_plane_normal;
    Vec3d frustum_top_plane_normal;
    Vec3d frustum_bottom_plane_normal;
    Vec3d frustum_origin_point;

};


#endif
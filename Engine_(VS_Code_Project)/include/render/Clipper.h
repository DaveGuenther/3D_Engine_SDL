#ifndef CLIPPER_H
#define CLIPPER_H
#include <vector>
#include "utility/Triangle.h"
#include "utility/Vec3d.h"
#include "render/Camera.h"
#include "render/Frustum.h"


class Clipper{
    private:
        Vec3d frustum_front_plane_normal = Vec3d(0.0f, 0.0f, 1.0f);
        Vec3d frustum_front_point;
        Vec3d frustum_left_plane_normal;
        Vec3d frustum_top_plane_normal = Vec3d(0.0f, -1.0f, 1.0f);
        Vec3d frustum_right_plane_normal;
        Vec3d frustum_bottom_plane_normal = Vec3d(0.0f, 1.0f, 1.0f);
        Vec3d frustum_origin_point = Vec3d(0.0f, 0.0f, 0.0f);
        Triangle triView;
        std::vector<Triangle> frustum_clipped_tris;
        Frustum* thisCameraFrustum;

    public:
        Clipper(Camera* thisCamera);
        std::vector<Triangle>& getClippedTrisAgainstFrustum(float AspectRatio, Triangle& triView, float distToFrontFrustumPlane);





};

#endif
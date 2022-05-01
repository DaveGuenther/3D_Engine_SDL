#include "render/Clipper.h"
#include "utility/Vector_Math_Service.h"
#include "utility/Triangle.h"

Clipper::Clipper(Camera* thisCamera):thisCameraFrustum(thisCamera->cameraViewFrustum){}

std::vector<Triangle>& Clipper::getClippedTrisAgainstFrustum(float AspectRatio, Triangle& triView, float distToFrontFrustumPlane){
    this->frustum_clipped_tris.clear();

    this->frustum_front_plane_normal = Vec3d(0.0f, 0.0f, 1.0f);
    this->frustum_front_point = Vec3d(0.0f, 0.0f, distToFrontFrustumPlane);

    this->frustum_left_plane_normal = Vec3d(AspectRatio, 0.0f, 1.0f);
    this->frustum_right_plane_normal=(Vec3d(-1*AspectRatio, 0.0f, 1.0f));
    this->frustum_top_plane_normal = Vec3d(0.0f, -1.0f, 1.0f);
    this->frustum_bottom_plane_normal = Vec3d(0.0f, 1.0f, 1.0f);
    this->frustum_origin_point = Vec3d(0.0f, 0.0f, 0.0f);

    // Clip triangle against z_near plane
    int nClippedTriangles=0;
    Triangle clipped[2];
    nClippedTriangles = VectorMathService::clipTriangleWithPlane(frustum_front_point, frustum_front_plane_normal, triView, clipped[0], clipped[1]);
    std::vector<Triangle> front_clipped_tris, left_clipped_tris, top_clipped_tris, right_clipped_tris; 
    for (int n=0; n< nClippedTriangles; n++){
        front_clipped_tris.push_back(clipped[n]);
    }
    // Test along left frustum edge
    for (Triangle this_tri:front_clipped_tris){
        nClippedTriangles = VectorMathService::clipTriangleWithPlane(frustum_origin_point, frustum_left_plane_normal, this_tri, clipped[0], clipped[1]);
        for (int n=0;n<nClippedTriangles;n++){
            left_clipped_tris.push_back(clipped[n]);
        }
    }

    // Test along top frustum edge
    for (Triangle this_tri:left_clipped_tris){
        nClippedTriangles = VectorMathService::clipTriangleWithPlane(frustum_origin_point, frustum_top_plane_normal, this_tri, clipped[0], clipped[1]);
        for (int n=0;n<nClippedTriangles;n++){
            top_clipped_tris.push_back(clipped[n]);
        }
    }

    // Test along right frustum edge Vec3d(-1*this->fAspectRatio, 0.0f, 1.0f)
    for (Triangle this_tri:top_clipped_tris){
        nClippedTriangles = VectorMathService::clipTriangleWithPlane(frustum_origin_point, frustum_right_plane_normal, this_tri, clipped[0], clipped[1]);
        for (int n=0;n<nClippedTriangles;n++){
            right_clipped_tris.push_back(clipped[n]);
        }
    }

    // Test along bottom frustum edge
    for (Triangle this_tri:right_clipped_tris){
        nClippedTriangles = VectorMathService::clipTriangleWithPlane(frustum_origin_point, frustum_bottom_plane_normal, this_tri, clipped[0], clipped[1]);
        for (int n=0;n<nClippedTriangles;n++){
            this->frustum_clipped_tris.push_back(clipped[n]);
        }
    }

    return this->frustum_clipped_tris;
}
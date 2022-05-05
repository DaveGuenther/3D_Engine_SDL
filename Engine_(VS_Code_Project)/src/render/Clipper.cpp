#include <memory>
#include "render/Clipper.h"
#include "utility/Vector_Math_Service.h"
#include "utility/Triangle.h"

Clipper::Clipper(std::shared_ptr<Camera> thisCamera):thisCameraFrustum(thisCamera->cameraViewFrustum){
    this->frustum_bottom_plane_normal = this->thisCameraFrustum->getFrustumBottomPlaneNormal();
    this->frustum_front_plane_normal = this->thisCameraFrustum->getFrustumFrontPlaneNormal();
    this->frustum_front_point = this->thisCameraFrustum->getFrustumFrontPoint();
    this->frustum_left_plane_normal = this->thisCameraFrustum->getFrustumLeftPlaneNormal();
    this->frustum_origin_point = this->thisCameraFrustum->getFrustumOriginPoint();
    this->frustum_right_plane_normal = this->thisCameraFrustum->getFrustumRightPlaneNormal();
    this->frustum_top_plane_normal = this->thisCameraFrustum->getFrustumTopPlaneNormal();

}

std::vector<Triangle>& Clipper::getClippedTrisAgainstFrustum(Triangle& triView){
    this->frustum_clipped_tris.clear();

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
#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "../utility/Vec3d.h"

/**
 * @brief This class contains information about the Frustum edges of a camera used for determining when to draw objects or not and for clipping in viewSpace.
 * If the frustum is projected to 2D screenSpace, it becomes the left, top, right, and bottom edges of the screen.  The frustum edges are all defined by having a
 * normal vector for the frustum plane and a point on the plane.  The left, top, right, and bottom frustum planes all share the same point on the frustum plane 
 * (frustum_origin_point).  The front frustum plane is defined by the frustum_front_plane_normal and the frustum_front_point.  A picture would be helpful here...
 * 
 *                      Frustum                                                     Frustum
 *                   Top Down View                                                 Side View
 *                  ---------------                                                   /|    
 *                  \             / --frustum_right_plane              top_plane -- /  |
 *       frustum_  -- \         /                                                 /|   |
 *        left_plane    \-----/                           frustum_origin_point-- * |   |
 *                        \ / \                                                   \|   |
 *                         *   frustum_front_plane                   bottom_plane --\  |
 *                         |                                                          \|
 *      frustum_origin_point
 *      
 * Look at Frustum.h for a proper ascii view of the frustum diagram   
 */
class Frustum{
    public:
        /**
         * @brief Construct a new Frustum object
         * 
         * @param aspectRatio - this variable is required to define the left and right frustum edges
         */
        Frustum(float aspectRatio, float max_draw_dist);

        const Vec3d& getFrustumFrontPlaneNormal();
        const Vec3d& getFrustumFrontPoint();
        const Vec3d& getFrustumLeftPlaneNormal();
        const Vec3d& getFrustumRightPlaneNormal();
        const Vec3d& getFrustumTopPlaneNormal();
        const Vec3d& getFrustumBottomPlaneNormal();
        const Vec3d& getFrustumOriginPoint();
        const Vec3d& getFrustrumBackPlaneNormal();
        const Vec3d& getFrustrumBackPoint();


    private: 
    Vec3d frustum_front_plane_normal;
    Vec3d frustum_front_point;

    Vec3d frustum_left_plane_normal;
    Vec3d frustum_right_plane_normal;
    Vec3d frustum_top_plane_normal;
    Vec3d frustum_bottom_plane_normal;
    Vec3d frustum_origin_point;

    // Attempting to define a back plane where nothing further is drawn.  This is an attempt to 
    // increase the framerate.  
    Vec3d frustrum_back_plane_normal; // I think this can be the inverse of the front plane normal
    Vec3d frustrum_back_point; // This can be the same as the max draw distance.  That point can be used to define the plane.

 
};


#endif
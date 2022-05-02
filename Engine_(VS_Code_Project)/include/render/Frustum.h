#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "utility/Vec3d.h"

/**
 * @brief This class contains information about the Frustum edges of a camera used for determining when to draw objects or not and for clipping in viewSpace.
 * If the frustum is projected to 2D screenSpace, it becomes the left, top, right, and bottom edges of the screen.  The frustum edges are all defined by having a
 * normal vector for the frustum plane and a point on the plane.  The left, top, right, and bottom frustum planes all share the same point on the frustum plane 
 * (frustum_origin_point).  The front frustum plane is defined by the frustum_front_plane_normal and the frustum_front_point.  A picture would really be helpful here...
 * 
 *                 Frustum                                    Frustum
 *              Top Down View                                Side View
 *             ---------------                                         /|    
 *             \             / --frustum_right_plane                 /  |
 *  frustum_  -- \         /                                       /|   |
 *   left_plane    \-----/                                        * |   |
 *                   \ / \                                         \|   |
 *                    *   \                                          \  |
 *                         frustum_front_plane                         \|
 * 
 *            
 * 
 * 
 * 
 */
class Frustum{
    public:
        /**
         * @brief Construct a new Frustum object
         * 
         * @param aspectRatio - this variable is required to define the left and right frustum edges
         */
        Frustum(float aspectRatio);

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
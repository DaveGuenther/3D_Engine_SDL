#ifndef CLIPPER_H
#define CLIPPER_H
#include <vector>
#include "../utility/Triangle.h"
#include "../utility/Vec3d.h"
#include "../render/Camera.h"
#include "../render/Frustum.h"

/**
 * @brief This class is responsible for clipping a single triangle in viewSpace against the front, left, top, right, and bottom frustum planes.
 * As it performs clipping on a triangle against each of the frustum edges, it will create new triangle(s) that terminate at the frustum edge.  It 
 * will produce a list of triangles that are to be drawn along the frustum edges to avoid drawing anything that isn't on screen.
 * 
 */
class Clipper{
    private:
        Vec3d frustum_front_plane_normal = Vec3d(0.0f, 0.0f, 1.0f);
        Vec3d frustum_front_point;
        Vec3d frustum_left_plane_normal;
        Vec3d frustum_top_plane_normal = Vec3d(0.0f, -1.0f, 1.0f);
        Vec3d frustum_right_plane_normal;
        Vec3d frustum_bottom_plane_normal = Vec3d(0.0f, 1.0f, 1.0f);
        Vec3d frustum_origin_point = Vec3d(0.0f, 0.0f, 0.0f);
        Vec3d frustum_back_plane_normal;
        Vec3d frustum_back_point;

        float fFOV;

        Triangle triView;
        std::vector<Triangle> frustum_clipped_tris;
        std::shared_ptr<Frustum> thisCameraFrustum;

    public:
        /**
         * @brief Construct a new Clipper object.  This is run once when the Renderer is instantiated
         * 
         * @param thisCamera this is passed in to access the frustum object used to define the frustum edges for clipping
         */
        Clipper(std::shared_ptr<Camera> thisCamera, float fFOV);
        
        /**
         * @brief Get the Clipped Tris Against Frustum object.  This function is called once per triangle that is being projected from 3D viewSpace 
         * to 2D screenSpace.
         * 
         * @param triView - This is a reference to the triangle in viewSpace that needs to be clipped against the frustum edges
         * @return std::vector<Triangle>& - This is a list of triangles in viewSpace that are clipped against the frustum edges.  When this list 
         * of triangles is drawn, it will resemble the original triangle in viewSpace, except that no part of the triangle will be drawn outside
         * the frustum edges (or off screen in 2D screenSpace).
         */
        std::vector<Triangle>& getClippedTrisAgainstFrustum(Triangle& triView);





};

#endif
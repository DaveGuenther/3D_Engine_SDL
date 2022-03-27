#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "render/Renderer.h"
#include "utility/Vec2d.h"
#include <array>
#include <map>

/**
 * @brief this class will draw a rasterized Triangle form triangles in the projected screen space with depth values (not triangles in the world space)
 * 
 */
class Triangle_Rasterizer{
    private:
        Vec2d tri_boundary_min, tri_boundary_max;  // These two points together represent a rectangle bounding box for the triangle that we want to rasterize
        Vec3d v0, v1, v2;
        int width, height;
        std::map<int, std::map<int, int>> my_bitmap;
        //std::vector<std::vector<bool>> my_bitmap;
        bool isPixelContainedIn2dTriangle(float x, float y);
        void createBitmap();

    public:
        Triangle_Rasterizer(Triangle& this_triangle);
        const std::map<int, std::map<int, int>>& getBitmap();
        const Vec2d getBitmapStartPos();
        const Vec2d getBitmapSize();

};

#endif
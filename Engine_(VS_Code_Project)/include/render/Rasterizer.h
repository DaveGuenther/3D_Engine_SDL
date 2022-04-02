#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "render/Renderer.h"
#include "utility/Vec2d.h"
#include <array>
#include <map>

class ITriangleRasterizer{
    protected:
        //Renderer* my_renderer;
        SDL_Renderer *renderer;
    
    public:
        void virtual drawTriangle(Triangle& this_triangle, SDL_Color col)=0;

};

/**
 * @brief this class will draw a rasterized Triangle from triangles in the projected screen space with depth values (not triangles in the world space).  This 
 * method uses the In-Out approach (Ray Tracing) to Rasterization
 * 
 */
class InOutRasterizer:public ITriangleRasterizer{
    public:
        InOutRasterizer(SDL_Renderer* my_renderer);
        ~InOutRasterizer();
        void drawTriangle(Triangle& this_triangle, SDL_Color col);
    
    private:
        bool isPixelContainedIn2dTriangle(int Px, int Py);
        int bound_box_min_x, bound_box_min_y, bound_box_max_x, bound_box_max_y;
        int v0_x, v0_y, v0_z, v1_x, v1_y, v1_z, v2_x, v2_y, v2_z;
        int width, height;

};

/**
 * @brief this class will draw a rasterized Triangle form triangles in the projected screen space with depth values (not triangles in the world space)
 * 
 */
class Triangle_Rasterizer{
    private:
        //Vec2d tri_boundary_min, tri_boundary_max;  // These two points together represent a rectangle bounding box for the triangle that we want to rasterize
        int bound_box_min_x, bound_box_min_y, bound_box_max_x, bound_box_max_y;
        int v0_x, v0_y, v0_z, v1_x, v1_y, v1_z, v2_x, v2_y, v2_z;
        
        //Vec3d v0, v1, v2;
        int width, height;
        std::map<int, std::map<int, bool>> my_bitmap;
        //std::vector<std::vector<bool>> my_bitmap;
        bool isPixelContainedIn2dTriangle(int x, int y);
        void createBitmap();

    public:
        Triangle_Rasterizer(Triangle& this_triangle);
        const std::map<int, std::map<int, bool>>& getBitmap();
        const Vec2d getBitmapStartPos();
        const Vec2d getBitmapSize();

};

#endif
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

class ScanlineRasterizer:public ITriangleRasterizer{
    public:
        ScanlineRasterizer(SDL_Renderer* my_renderer);
        void drawTriangle(Triangle& this_triangle, SDL_Color col);
    private:
        void drawFlatTopTri(Triangle& this_triangle, SDL_Color col);
        void drawFlatBottomTri(Triangle& this_triangle, SDL_Color col);
        
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



#endif
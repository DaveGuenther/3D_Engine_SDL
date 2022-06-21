#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "Renderer.h"
#include "utility/Vec2d.h"
#include "utility/PNGTexture.h"
#include <array>
#include <map>

class ITriangleRasterizer{
    protected:
        //Renderer* my_renderer;
        SDL_Renderer *renderer;
        float max_visible_z_depth = 2.0f;  // distance from the camera at which things are no lonver visible
        float min_visible_color_modifier = 0.1f; // minimum scalar for triangle colors (R, G, B) values are multiplied by this in order to dim a color
    
    public:
    /**
     * @brief Rasterizes a triangle in pixel space
     * 
     * @param this_triangle 
     */
        void virtual drawTriangle(Triangle& this_triangle)=0;

        
        /**
         * @brief Given an (r,g,b) SDL_Color and a triangle, this function will dim the color based on how far away from the player the triangle is.
         * 
         * @param this_tri
         * @param col 
         * 
         */
        void applyDepthDimmer(Triangle& this_tri, SDL_Color &col);

};

class TexturemapRasterizer:public ITriangleRasterizer{
    public:
        TexturemapRasterizer(SDL_Renderer* my_renderer, std::shared_ptr<PNGTexture> this_texture);
        void drawTriangle(Triangle& this_triangle);
        
    private:
        void drawFlatTopTri(Triangle& this_triangle);
        void drawFlatBottomTri(Triangle& this_triangle);
        std::shared_ptr<PNGTexture> this_texture;
        
};

class ScanlineRasterizer:public ITriangleRasterizer{
    public:
        ScanlineRasterizer(SDL_Renderer* my_renderer);
        void drawTriangle(Triangle& this_triangle);
        
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
        void drawTriangle(Triangle& this_triangle);
        
    
    private:
        bool isPixelContainedIn2dTriangle(int Px, int Py);
        int bound_box_min_x, bound_box_min_y, bound_box_max_x, bound_box_max_y;
        int v0_x, v0_y, v0_z, v1_x, v1_y, v1_z, v2_x, v2_y, v2_z;
        int width, height;

};



#endif
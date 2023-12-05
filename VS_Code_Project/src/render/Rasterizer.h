#ifndef RASTERIZER_H
#define RASTERIZER_H
#include <array>
#include <map>

#include "Renderer.h"
#include "../utility/Vec2d.h"
#include "../materials/TexturePNG.h"


class ITriangleRasterizer{
    protected:
        //Renderer* my_renderer;
        SDL_Renderer *renderer;
        float max_visible_z_depth = 5.0f;  // distance from the camera at which things are no lonver visible
        float inv_max_visible_z_depth;
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
        TexturemapRasterizer(SDL_Renderer* my_renderer);
        void drawTriangle(Triangle& this_triangle);
        
    private:
        //Functions for both flat top and flat bottom
        void texelDetermineAlphaX();
        void texelDetermineUV(Triangle& this_triangle);
        void texelDimPixel(Triangle& this_triangle);
        void texelDrawUV_Point();
        void scanlineDetermineDist();
        void scanlineCalcStartEnd(Triangle &this_triangle);
        void drawTriangleInitializer(Triangle &this_triangle);
        
        //Functions specific to FT or FB
        void drawFT_CalcSlopes(Triangle &this_triangle);
        void drawFT_Scanline_prep(Triangle &this_triangle);
        void drawFB_CalcSlopes(Triangle &this_triangle);
        void drawFB_Scanline_prep(Triangle &this_triangle);
        void drawFlatTopTri(Triangle& this_triangle);
        void drawFlatBottomTri(Triangle& this_triangle);
        
        //std::shared_ptr<TexturePNG> this_texture;
        TexturePNG* this_texture;
        
        ///// FlatTop and FlatBottom Triangle Data members are instantiated here and then data is overwritten during each
        ///// run of drawFlatTopTri or drawFlatBottomTri routines.  Instead of creating and destroying all these data members each
        ///// cycle, we'll use these and pass by ref everywhere to control overwriting.
        
        //Triangle vars
        //std::shared_ptr<TexturePNG> texture;
        Vec3d p0, p1, p2;
        Vec2d uv0, uv1, uv2;
        float left_slope, right_slope, inv_left_slope_denom, inv_right_slope_demon;
        int y_start, y_end;

        //vertical scanline vars
        int y, x_start, x_end;
        float p_start, p_end, alpha_start, alpha_end, UVx_start, UVy_start, UVz_start, UVx_end, UVy_end, UVz_end, inv_scanline_dist;

        //pixel vars
        int x;
        float alpha_scan, UVx_scan, UVy_scan, inv_UVz_scan;
        SDL_Color col={255,255,255,255};

        ///// end of FlatTop and FlatBottom variables
        

};

class ScanlineRasterizer:public ITriangleRasterizer{
    public:
        ScanlineRasterizer(SDL_Renderer* my_renderer);
        void drawTriangle(Triangle& this_triangle);
        
    private:
        void drawFlatTopTri(Triangle& this_triangle, SDL_Color col);
        void drawFlatBottomTri(Triangle& this_triangle, SDL_Color col);
        
};



#endif
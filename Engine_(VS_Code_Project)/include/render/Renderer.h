#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL2/SDL.h>

#include "utility/Mesh.h"
#include "utility/Vec2d.h"
#include "utility/Vec3d.h"
#include "utility/Mat4x4.h"
#include "utility/Mesh_Pipeline.h"
#include "Renderer.h"





/**
 * @brief The Renderer class will manage all draw operaions of the engine.
 * 
 */
class Renderer{
    private:
        // SDL Objects
        SDL_Window *window;
        SDL_Renderer *renderer;

        int SCREEN_W;
        int SCREEN_H;
        int screen_mode=0;  // 0 for Windowed, 1 for Fullscreen

        // Projection Matrix
        float fNear;
        float fFar;
        float fFOV;
        float fAspectRatio;
        float fFOV_rad;

        Vec3d camera;

        Mat4x4 matProj;  //[row][column]

        /**
         * @brief Draw a point (or specific icon) at the center of the screen to represent the player's reticle
         * 
         */
        void drawReticle();

        /**
         * @brief Engine_3D operates in a 3D Cartesian coordinate space with 0,0,0 being the true center spot of the world.  Likewise, 0,0 would be the true center of the screen in cartesian space.  This method will convert cartesian coordinates to screen coordinates factoring in the screen resolution.
         * 
         * @param this_point a 2D point in the cartesian coordinate space
         * @return Vec2d a 2D point converted to screen coordinates
         */
        Vec2d cartesianToScreen(Vec2d this_point);

        /**
         * @brief This method applies the projection matrix to a Triangle object in 3D space.  The Triangle object is modified in place.
         * 
         * @param tri 
         */
        void projectTriangle3d(Triangle &tri);

        /**
         * @brief Given a Triangle with x and y projected to screen space and z in world space, this method will draw a wireframe triangle to the screen using lines
         * 
         * @param this_triangle Triangle object with x, and y vertices in projected screen space [-1.0, 1.0] and z vertex in world space
         * @param col SDL color to plot the wireframe triangle edges
         */
        void drawWireFrameTriangle2d(Triangle this_triangle, SDL_Color col);

        /**
         *
         * @brief Given a Triangle with x and y projected to screen space and z in world space, this method will draw a filled triangle on the screen using a simple rasterization algorithm.  This methos will implement the Rasterization class
         * 
         * @param this_triangle Triangle object with x, and y vertices in projected screen space [-1.0, 1.0] and z vertex in world space
         * @param col SDL color to fill the triangle
         */
        void drawFilledTriangle2d(Triangle this_triangle, SDL_Color col);

    public:

        Renderer(int SCREEN_W, int SCREEN_H);
        
        /**
         * @brief This function will reset the mouse X and Y values to the center of the window.  It requires the window object to call so must occur in the Renderer class
         * 
         */
        void resetMouseXY();
    
        void setWindowTitle(std::string title);
        
        
        /**
         * @brief This method directs the projection operations over the entire mesh pipeline.  It iterates through each mesh and it's tris in order to apply projections and direct screen page drawing
         * 
         * @param this_mesh_pipeline 
         */
        void refreshScreen(Mesh_Pipeline* this_mesh_pipeline);  // Why can't I make this a const pointer?

        const int getWindowWidth() const;
        const int getWindowHeight() const;

        /**
         * @brief this method is mainly used to shut down the SDL renderer and window objects
         * 
         */
        void shutdown();
};

#endif
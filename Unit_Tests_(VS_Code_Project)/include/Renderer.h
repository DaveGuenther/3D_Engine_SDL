#ifndef RENDERER_H
#define RENDERER_H


#include <vector>
#include <SDL2/SDL.h>

#include "Mesh.h"
#include "Vec2d.h"
#include "Vec3d.h"
#include "Mat4x4.h"
#include "Renderer.h"
#include "Mesh_Pipeline.h"




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

        Mat4x4 matProj, mat_XRot, mat_ZRot;  //[row][column]

        /**
         * @brief Draw a point (or specific icon) at the center of the screen to represent the player's reticle
         * 
         */
        void Draw_Reticle();

        /**
         * @brief Engine_3D operates in a 3D Cartesian coordinate space with 0,0,0 being the true center spot of the world.  Likewise, 0,0 would be the true center of the screen in cartesian space.  This method will convert cartesian coordinates to screen coordinates factoring in the screen resolution.
         * 
         * @param this_point a 2D point in the cartesian coordinate space
         * @return Vec2d a 2D point converted to screen coordinates
         */
        Vec2d Cartesian_to_Screen(Vec2d this_point);

        /**
         * @brief This method applies the projection matrix to a Triangle object in 3D space.  The Triangle object is modified in place.
         * 
         * @param tri 
         */
        void Project_Triangle_3d(Triangle &tri);

        /**
         * @brief Given three 2D points, this method will draw a triangle on the screen page.  Triangles are defined in clockwise point order when looking at the triangle face on (right-hand rule)
         * 
         * @param vert1 
         * @param vert2 
         * @param vert3 
         * @param col SDL color to plo the wireframe triangle
         */
        void Draw_Triangle_2d(Vec2d vert1, Vec2d vert2, Vec2d vert3, SDL_Color col);

    public:

        Renderer();

        /**
         * @brief This method directs the projection operations over the entire mesh pipeline.  It iterates through each mesh and it's tris in order to apply projections and direct screen page drawing
         * 
         * @param this_mesh_pipeline 
         */
        void Refresh_Screen(Mesh_Pipeline &this_mesh_pipeline);

        /**
         * @brief this method is mainly used to shut down the SDL renderer and window objects
         * 
         */
        void shutdown();
};

#endif
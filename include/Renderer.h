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

        void Draw_Reticle();
        Vec2d Cartesian_to_Screen(Vec2d this_point);
        void Project_Triangle_3d(Triangle &tri);
        void Draw_Triangle_2d(Vec2d vert1, Vec2d vert2, Vec2d vert3, SDL_Color col);

    public:

        Renderer();
        void Refresh_Screen(Mesh_Pipeline &this_mesh_pipeline);
        void shutdown();
};

#endif
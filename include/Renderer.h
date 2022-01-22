#ifndef RENDERER_H
#define RENDERER_H


#include <vector>
#include <SDL2/SDL.h>

#include "Mesh.h"
#include "vec2d.h"
#include "mat4x4.h"
#include "Renderer.h"





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

        mat4x4 matProj, mat_XRot, mat_ZRot;  //[row][column]

        vec2d cart_to_screen(vec2d this_point);

    public:

        Renderer();
        void UpdateScreen(const std::vector<Mesh> &mesh_pipe);
        void shutdown();
};

#endif
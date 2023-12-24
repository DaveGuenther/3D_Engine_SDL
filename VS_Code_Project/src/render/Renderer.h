#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include <SDL2/SDL.h>

#include "../utility/Mesh.h"
#include "../utility/Vec2d.h"
#include "../utility/Vec3d.h"
#include "../utility/Mat4x4.h"
#include "../utility/Mesh_Pipeline.h"
#include "../render/SDLTextureBlit.h"
#include "../render/TrianglePipeline.h"
#include "../render/Camera.h"
#include "../render/Clipper.h"





/**
 * @brief The Renderer class will manage all draw operaions of the engine.
 * 
 */
class Renderer{
    private:
        typedef struct {
            SDL_Window *window;
            SDL_Renderer *renderer;
            
            // Variables for the Window itself that we associate with the Renderer
            uint32_t WINDOW_W; // This is the width of the window that we want to render the image to
            uint32_t WINDOW_H; // This is the height of the window that we want to render the image to
            uint32_t HALF_WINDOW_W; // Half the window width -- used to place a window in the middle of the desktop
            uint32_t HALF_WINDOW_H; // Half the window height -- used to place a window in the middle of the desktop
            uint32_t window_mode=0;  // 0 for Windowed, 1 for Fullscreen, 128 for full screen maximized, SDL_WINDOW_RESIZABLE
            SDL_Rect windowRect; // This rectangle is used during SDL_RenderCopy()

            // Variables for the rendering area (frame Buffer) that we'll draw on and stretch to the window size when we copy it to the renderer
            SDL_Texture_LineBlit *textureBlit = NULL;
            uint32_t SCREEN_W; // This is the width of the framebuffer we want to draw to
            uint32_t SCREEN_H; // This is the width of the framebuffer we want to draw to
            uint32_t HALF_SCREEN_W; // This half the width of the framebuffer we want to draw to 
            uint32_t HALF_SCREEN_H; // This half the height of the framebuffer we want to draw to
            uint32_t fFOV;
            uint32_t fAspectRatio;  // Screen Height/Width
            float fFOV_rad; // This is the FOV in radians
            
        } rendererStruct;
        
        // SDL Objects
        rendererStruct rendererData;
        

        

        
        // Projection Matrix
        float fNear;
        float fFar;
        //float fFOV;
        //float fAspectRatio;
        //float fFOV_rad;

        std::shared_ptr<Camera> player_camera;
        std::shared_ptr<Clipper> thisFrustumClipper;
        //Clipper* thisFrustumClipper;
        Mat4x4 matView;
        float max_visible_z_depth; // distance from the camera at which things are no lonver visible
        float inv_max_visible_z_depth; // used to avoid divising by max_visible_z_depth a bunch of times
        float min_visible_color_modifier = 0.1f; // minimum scalar for triangle colors (R, G, B) values are multiplied by this in order to dim a color
        Uint8 min_red_value, min_green_value, min_blue_value;
        
        std::vector<Triangle> trianglesToRasterize;

        bool colorFrustumClippedTris=true;

        Mat4x4 matProj;  //[row][column]

        /**
         * @brief Draw a point (or specific icon) at the center of the screen to represent the player's reticle
         * 
         */
        void drawReticle();

        float applyDepthDimmerModifier(Triangle& this_tri);
        SDL_Color applyDepthDimmer(Triangle& this_tri);

        /**
         * @brief Engine_3D operates in a 3D Cartesian coordinate space with 0,0,0 being the true center spot of the world.  Likewise, 0,0 would be the true center of the screen in cartesian space.  This method will convert cartesian coordinates to screen coordinates factoring in the screen resolution.
         * 
         * @param this_point a 2D point in the cartesian coordinate space
         * @return Vec2d a 2D point converted to screen coordinates
         */
        Vec2d cartesianToScreen(Vec2d this_point);
        void cartesianToScreen_inplace(Vec2d& this_point);

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
         */
        void drawWireFrameTriangle2d(Triangle this_triangle);

        /**
         *
         * @brief Given a Triangle with x and y projected to screen space and z in world space, this method will draw a filled triangle on the screen using a simple rasterization algorithm.  This methos will implement the Rasterization class
         * 
         * @param this_triangle Triangle object with x, and y vertices in projected screen space [-1.0, 1.0] and z vertex in world space
         */
        void drawFilledTriangle2d(Triangle this_triangle);



    public:
        
        Renderer(uint32_t SCREEN_W, uint32_t SCREEN_H, uint32_t WINDOW_W, uint32_t WINDOW_H, std::shared_ptr<Camera> player_camera, float FOV);
        ~Renderer();
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
        void refreshScreen(std::shared_ptr<TrianglePipeline> my_pre_renderer);  // Why can't I make this a const pointer?

        const int getWindowWidth() const;
        const int getWindowHeight() const;

        void setColorFrustumClippedTris(bool value);

        /**
         * @brief this method is mainly used to shut down the SDL renderer and window objects
         * 
         */
        void shutdown();
};

#endif
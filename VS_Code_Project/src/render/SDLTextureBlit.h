#ifndef SDL_TEXTURE_BLIT_H
#define SDL_TEXTURE_BLIT_H

#include <SDL2/SDL.h>

/*
How to use:
-Instantiate from scope that has an SDL_Renderer* defined with dimensions of pixelbuffer then run these commands in sequece during the game loop
  -lock() the texture so it can be edited
  -blit() pixels to the texture as muich as you want (use RGBA8888 format for now)
  -unlock() the texture so that it's ready for the render
  -RenderCopy() to apply the texture to the renderer.

- Outside this class, present the renderer using SDL_RenderPresent(renderer); to show the pixel buffer
The instance of this class should be destroyed when the calling object goes out of scope (just before it destroys the SDL_Renderer object).
*/

class SDL_Texture_Blit{
    public:
        SDL_Texture_Blit(SDL_Renderer* renderer, int SCREEN_W, int SCREEN_H);
        ~SDL_Texture_Blit();
        void lock(); // Do this before blitting
        void blit(uint x, uint y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        void unlock(); // do this when all the pixel blits are done for the frame
        void RenderCopy(); // Copies the unlocked terxture to the renderer
        SDL_Texture* getFrameBuffer(); // use this returned pointer to call SDL_RenderCopy(renderer, <frameBuffer>, NULL, NULL); outside this class

    private:
        SDL_Renderer *renderer=NULL;
        SDL_PixelFormat *pixelFormat=NULL;
        SDL_Texture *texture=NULL;
        int tex_w, tex_h;
        uint8_t *framebufferpixels=NULL;
        Uint32 *tex_head=NULL;
        Uint32 textureFormat;
        int pitch;
        Uint32 *p=NULL; // this will be the pixel pointer to a specific pixel in the buffer
        
        bool inPixelRange(const int &x, const int &y);

};


#endif
#ifndef SDL_TEXTURE_BLIT_H
#define SDL_TEXTURE_BLIT_H

#include <SDL2/SDL.h>

/*
How to use:
-Instantiate from scope that has an SDL_Renderer* defined with dimensions of pixelbuffer then run these commands in sequece during the game loop
  -lock() the texture so it can be edited
  -blit(), blitSequuential(), or blitLine() to place pixels on the texture as much as you want (use RGBA8888 format for now)
  -unlock() the texture so that it's ready for the render
  -RenderCopy() to apply the texture to the renderer.

- Outside this class, present the renderer using SDL_RenderPresent(renderer); to show the pixel buffer
The instance of this class should be destroyed when the calling object goes out of scope (just before it destroys the SDL_Renderer object).
*/

class SDL_Texture_Blit{
    private:

        bool inPixelRange(Uint32 x, Uint32 y);
        SDL_Renderer *renderer=NULL;
        SDL_PixelFormat *pixelFormat=NULL;
        SDL_Texture *texture=NULL;
        int tex_w, tex_h;
        uint8_t *framebufferpixels=NULL;
        Uint32 *tex_head=NULL;
        Uint32 textureFormat;
        int pitch=0; // size of one row in bytes
        Uint32 adjusted_pitch=0; // this is the pitch of a single row in pixels (not bytes)
        Uint32 *p=NULL; // this will be the pixel pointer to a specific pixel in the buffer
        SDL_Rect windowRect;
        bool validStartPos = false;
        Uint32 x;

    public:
        SDL_Texture_Blit(SDL_Renderer* renderer, uint32_t SCREEN_W, uint32_t SCREEN_H, uint32_t WINDOW_W, uint32_t WINDOW_H);
        SDL_Texture_Blit(SDL_Renderer* renderer, SDL_Texture* existingBuffer);
        ~SDL_Texture_Blit();    
        void blitPixel(Uint32 x, Uint32 y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        void blitSequential(uint8_t r, uint8_t g, uint8_t b); // blits and then advances the pixel ptr by 1 pixel (4 bytes).  Used for horizontal series of pixels
        void setXY_Start(Uint32 x, Uint32 y); // use with blitSequential to test that startpoint of blitSequential is in the window
        void blitLine( float x1, float y1, float x2, float y2, const SDL_Color& color );
        
        void lock(); // Do this before blitting
        void unlock(); // do this when all the pixel blits are done for the frame
        void RenderCopy(); // Copies the unlocked terxture to the renderer
        Uint32 getTex_w();
        Uint32 getTex_h();
        Uint32* getPixelPointer();
        SDL_PixelFormat* getPixelFormat();

        SDL_Texture* getFrameBuffer(); // use this returned pointer to call SDL_RenderCopy(renderer, <frameBuffer>, NULL, NULL); outside this class

};

#endif
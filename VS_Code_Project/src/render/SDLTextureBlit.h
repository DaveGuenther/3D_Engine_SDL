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

class I_SDL_Texture_Blit{
    protected:

        bool inPixelRange(const int &x, const int &y);
        
        SDL_Renderer *renderer=NULL;
        SDL_PixelFormat *pixelFormat=NULL;
        SDL_Texture *texture=NULL;
        int tex_w, tex_h;
        uint8_t *framebufferpixels=NULL;
        Uint32 *tex_head=NULL;
        Uint32 textureFormat;
        int pitch=0; // size of one row in bytes
        int adjusted_pitch=0; // this is the pitch of a single row in pixels (not bytes)
        Uint32 *p=NULL; // this will be the pixel pointer to a specific pixel in the buffer
 

    public:
        void lock(); // Do this before blitting
        void unlock(); // do this when all the pixel blits are done for the frame
        void RenderCopy(); // Copies the unlocked terxture to the renderer
        SDL_Texture* getFrameBuffer(); // use this returned pointer to call SDL_RenderCopy(renderer, <frameBuffer>, NULL, NULL); outside this class
        

};

class SDL_Texture_Blit:public I_SDL_Texture_Blit{
    public:
        SDL_Texture_Blit(SDL_Renderer* renderer, int SCREEN_W, int SCREEN_H);
        SDL_Texture_Blit(SDL_Renderer* renderer, SDL_Texture* existingBuffer);
        ~SDL_Texture_Blit();    
        void blit(uint x, uint y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
};


/**
 * This is a special implementation of the I_SDL_Texture_Blit Interface that lets us set the y value we are working with ahead of time,
 * pick a starting X coordinate on that Y line and render pixels (each blit function increments the pixel pointer on pixel in order) to an 
 * ending X coordinate on that Y line, then this class will increment the 
*/
class SDL_Texture_LineBlit:public I_SDL_Texture_Blit{
    public:
        SDL_Texture_LineBlit(SDL_Renderer* renderer, int SCREEN_W, int SCREEN_H);
        SDL_Texture_LineBlit(SDL_Renderer* renderer, SDL_Texture* existingBuffer);
        ~SDL_Texture_LineBlit();
        void blitAdvance(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        void setXY_Start(uint x, uint y);

    private:
        bool inX_Range(const int &x);
        bool validStartPos = false;
        uint x;
};


#endif
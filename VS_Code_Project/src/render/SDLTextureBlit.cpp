#include "SDLTextureBlit.h"
#include <SDL2/SDL.h>


SDL_Texture_Blit::SDL_Texture_Blit(SDL_Renderer* renderer, int SCREEN_W, int SCREEN_H){
    this->renderer = renderer;
    this->pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
    SDL_QueryTexture(this->texture, &this->textureFormat, NULL, &this->tex_w, &this->tex_h);
}

void SDL_Texture_Blit::lock(){
    SDL_LockTexture(this->texture, NULL, (void **)&this->framebufferpixels, &this->pitch);
    this->adjusted_pitch=this->adjusted_pitch/this->pixelFormat->BytesPerPixel;
    this->p = (Uint32 *)(this->framebufferpixels); // cast for a pointer increments by 4 bytes.(RGBA)
    this->tex_head=this->p;
}

void SDL_Texture_Blit::blit(uint x, uint y, uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    //this->p = this->tex_head+(this->pitch*y)+x;
    //*p = SDL_MapRGBA(this->pixelFormat, r, g, b, a);
    if (this->inPixelRange(x, y)){
        this->p = this->tex_head+(this->adjusted_pitch*y)+x;
        *p = SDL_MapRGBA(this->pixelFormat, r, g, b, a);
    }
}

void SDL_Texture_Blit::unlock(){
    SDL_UnlockTexture(this->texture);
}

void SDL_Texture_Blit::RenderCopy(){
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
}

SDL_Texture* SDL_Texture_Blit::getFrameBuffer(){
    return this->texture;
}

SDL_Texture_Blit::~SDL_Texture_Blit(){

    SDL_DestroyTexture(this->texture); // this also clears framebufferpixels
    free(this->pixelFormat); 
    p=NULL;
    tex_head=NULL;
    framebufferpixels=NULL;
    //SDL_Renderer* renderer gets destroyed by parent object outside this class
}

bool SDL_Texture_Blit::inPixelRange(const int &x, const int &y){
    if (y>this->tex_h) {return false;}
    if (x>this->tex_w) {return false;}
    if (y<0) {return false;}
    if (x<0) {return false;}
    return true;

}
#include "SDLTextureBlit.h"
#include <SDL2/SDL.h>
#include <iostream>


void I_SDL_Texture_Blit::lock(){
    if(SDL_LockTexture(this->texture, NULL, (void **)&this->framebufferpixels, &this->pitch))
    {
        // if return status is non-zero we have an error and want to show it here
        std::cout << "Error Locking Texture: " << SDL_GetError() << std::endl;
    }
    this->adjusted_pitch=this->pitch/this->pixelFormat->BytesPerPixel;
    this->p = (Uint32 *)(this->framebufferpixels); // cast for a pointer increments by 4 bytes.(RGBA)
    this->tex_head=this->p;
    
}

void I_SDL_Texture_Blit::unlock(){
    SDL_UnlockTexture(this->texture);
}

void I_SDL_Texture_Blit::RenderCopy(){
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
}

int I_SDL_Texture_Blit::getTex_h(){
    return this->tex_h;
}

int I_SDL_Texture_Blit::getTex_w(){
    return this->tex_w;
}

SDL_Texture* I_SDL_Texture_Blit::getFrameBuffer(){
    return this->texture;
}

bool I_SDL_Texture_Blit::inPixelRange(const int &x, const int &y){
    
    if (y>=this->tex_h) {return false;}
    if (x>=this->tex_w) {return false;}
    if (y<0) {return false;}
    if (x<0) {return false;}
    return true;

}

SDL_Texture_Blit::SDL_Texture_Blit(SDL_Renderer* renderer, int SCREEN_W, int SCREEN_H){
    
    this->renderer = renderer;
    this->pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
    SDL_QueryTexture(this->texture, &this->textureFormat, NULL, &this->tex_w, &this->tex_h);
    
}

SDL_Texture_Blit::SDL_Texture_Blit(SDL_Renderer* renderer, SDL_Texture* existingBuffer){
    this->renderer=renderer;
    this->pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    this->texture=existingBuffer;
    SDL_QueryTexture(this->texture, &this->textureFormat, NULL, &this->tex_w, &this->tex_h);
}

SDL_Texture_Blit::~SDL_Texture_Blit(){
    
    SDL_DestroyTexture(this->texture); // this also clears framebufferpixels
    free(this->pixelFormat); 
    p=NULL;
    tex_head=NULL;
    framebufferpixels=NULL;
    //SDL_Renderer* renderer gets destroyed by parent object outside this class
    
}

void SDL_Texture_Blit::blit(uint x, uint y, uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    //if ((y>=0 && y<this->tex_h) && (x>=0 && x<this->tex_w)){
    //if(this->inPixelRange(x, y)){
    this->p = this->tex_head+(this->adjusted_pitch*y)+x;
    *p = SDL_MapRGBA(this->pixelFormat, r, g, b, a);
    //}
}

SDL_Texture_LineBlit::SDL_Texture_LineBlit(SDL_Renderer* renderer, int SCREEN_W, int SCREEN_H){
    
    this->renderer = renderer;
    this->pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
    SDL_QueryTexture(this->texture, &this->textureFormat, NULL, &this->tex_w, &this->tex_h);
    
}

SDL_Texture_LineBlit::SDL_Texture_LineBlit(SDL_Renderer* renderer, SDL_Texture* existingBuffer){
    this->renderer=renderer;
    this->pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    this->texture=existingBuffer;
    SDL_QueryTexture(this->texture, &this->textureFormat, NULL, &this->tex_w, &this->tex_h);
}

SDL_Texture_LineBlit::~SDL_Texture_LineBlit(){
    
    SDL_DestroyTexture(this->texture); // this also clears framebufferpixels
    free(this->pixelFormat); 
    p=NULL;
    tex_head=NULL;
    framebufferpixels=NULL;
    //SDL_Renderer* renderer gets destroyed by parent object outside this class
    
}

bool SDL_Texture_LineBlit::inX_Range(const int &x){
    if (x>=this->tex_w) {return false;}
    if (x<0) {return false;}
    return true;
}

void SDL_Texture_LineBlit::setXY_Start(uint x, uint y){
    this->validStartPos = this->inPixelRange(x,y);
    if (this->validStartPos==true){
        this->p = this->tex_head+(this->adjusted_pitch*y)+x;
        this->x = x;
    }
}

void SDL_Texture_LineBlit::blitAdvance(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    if (this->validStartPos && this->inX_Range(x)){
        *p = SDL_MapRGBA(this->pixelFormat, r, g, b, a);
        this->p++;
        this->x++;
    }
}
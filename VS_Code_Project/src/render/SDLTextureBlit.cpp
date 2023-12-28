#include "SDLTextureBlit.h"
#include "../globals.h"
#include "../core/Console_Variables.h"
#include <SDL2/SDL.h>
#include <iostream>

SDL_Texture_Blit::SDL_Texture_Blit(SDL_Renderer* renderer, uint32_t SCREEN_W, uint32_t SCREEN_H, uint32_t WINDOW_W, uint32_t WINDOW_H, ConsoleData* console_data){
    
    this->renderer = renderer;
    this->pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);
    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888,SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
    SDL_QueryTexture(this->texture, &this->textureFormat, NULL, &this->tex_w, &this->tex_h);

    this->windowRect.x=0;
    this->windowRect.y=0;
    this->windowRect.w=WINDOW_W;
    this->windowRect.h=WINDOW_H;

    this->consoleData = console_data;
}

SDL_Texture_Blit::~SDL_Texture_Blit(){
    SDL_DestroyTexture(this->texture); // this also clears framebufferpixels
    free(this->pixelFormat); 
    p=NULL;
    tex_head=NULL;
    framebufferpixels=NULL;
    //SDL_Renderer* renderer gets destroyed by parent object outside this class
}

void SDL_Texture_Blit::lock(){
    if(SDL_LockTexture(this->texture, NULL, (void **)&this->framebufferpixels, &this->pitch))
    {
        // if return status is non-zero we have an error and want to show it here
        std::cout << "Error Locking Texture: " << SDL_GetError() << std::endl;
    }
    this->adjusted_pitch=this->pitch/this->pixelFormat->BytesPerPixel;
    this->p = (Uint32 *)(this->framebufferpixels); // cast for a pointer increments by 4 bytes.(RGBA)
    this->tex_head=this->p;
}

void SDL_Texture_Blit::unlock(){
    SDL_UnlockTexture(this->texture);
}

void SDL_Texture_Blit::RenderCopy(){
    //std::cout << (this->windowRect.w) <<  (this->windowRect.h) << std::endl; 
    //SDL_RenderCopy(this->renderer, this->texture, NULL, &this->windowRect);
    
    if (consoleData->renderer.renderScreenType!=WINDOW_FULLSCREEN && consoleData->renderer.renderScreenType!=WINDOW_FULLSCREEN_DESKTOP){
        SDL_RenderCopy(this->renderer, this->texture, NULL, &this->windowRect);
    }
    else{
        SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    }
}

Uint32 SDL_Texture_Blit::getTex_h(){
    return this->tex_h;
}

Uint32 SDL_Texture_Blit::getTex_w(){
    return this->tex_w;
}

SDL_Texture* SDL_Texture_Blit::getFrameBuffer(){
    return this->texture;
}

bool SDL_Texture_Blit::inPixelRange(Uint32 x, Uint32 y){
    if (y>=this->tex_h) {return false;}
    if (x>=this->tex_w) {return false;}
    if (y<0) {return false;}
    if (x<0) {return false;}
    return true;
}

Uint32* SDL_Texture_Blit::getPixelPointer(){
    return this->p;
}

SDL_PixelFormat* SDL_Texture_Blit::getPixelFormat(){
    return this->pixelFormat;
}

void SDL_Texture_Blit::blitPixel(Uint32 x, Uint32 y, uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    if ((y>=0 && y<this->tex_h) && (x>=0 && x<this->tex_w)){
        this->p = this->tex_head+(this->adjusted_pitch*y)+x;
        *p = SDL_MapRGBA(this->pixelFormat, r, g, b, a);
    }
}


void SDL_Texture_Blit::setXY_Start(Uint32 x, Uint32 y){
    this->validStartPos = this->inPixelRange(x,y);
    if (this->validStartPos==true){
        this->p = this->tex_head+(this->adjusted_pitch*y)+x;
        this->x = x;
    }
}

void SDL_Texture_Blit::blitSequential(uint8_t r, uint8_t g, uint8_t b){
    if (this->validStartPos && (x<this->tex_w) && (x>=0)){
        *p = SDL_MapRGB(this->pixelFormat, r, g, b);
        this->p++;
        this->x++;
    }
}

void SDL_Texture_Blit::blitLine( float x1, float y1, float x2, float y2, const SDL_Color& color ){
    //  Based on stack exchange post: https://stackoverflow.com/a/11744792
    // Bresenham's line algorithm
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if(steep)
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if(x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const float dx = x2 - x1;
    const float dy = fabs(y2 - y1);

    float error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = (int)y1;

    const int maxX = (int)x2;

    

    for(int x=(int)x1; x<maxX; x++)
    {
        if(steep)
        {
            if (x>this->tex_h){ x = tex_h-1;}
            this->blitPixel(y,x, color.r, color.g, color.b, 255);
        }
        else
        {
            if (y>this->tex_h){ y = tex_h-1;}
            this->blitPixel(x,y, color.r, color.g, color.b, 255);
        }

        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}
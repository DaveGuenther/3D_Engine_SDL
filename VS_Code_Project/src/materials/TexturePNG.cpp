#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include "TexturePNG.h"
#include "../render/Renderer_Observer.h"


TexturePNG::TexturePNG(std::shared_ptr<RendererSubject> this_renderer_subject, const char* filename){
    
    std::shared_ptr<Renderer_Observer> rendererObserver(new Renderer_Observer(*this_renderer_subject));
    this->rendererObserver=rendererObserver;
    this->renderer = this->rendererObserver->getSDLRendererPointer();
    //uint8_t* pixels;
    int pitch;
    std::cout << "Loading: '" << filename << "' into VRAM...";
    
    std::shared_ptr<stbimageTexture> stbimageData(new stbimageTexture(this->renderer, filename));
    this->stbimage_texture = stbimageData;

    //Surface specific
    this->surface = stbimageData->getSurface();
    this->surface = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_RGB24,0);
    this->pixels = (uint8_t*)this->surface->pixels;
    this->Bpp = this->surface->format->BytesPerPixel;
    this->width = this->surface->w;
    this->height = this->surface->h;
    // End Surface Specific
    
    /*this->stbimage_texture->convertToTextureSTREAMING();
    this->texture = this->stbimage_texture->getTextureSTREAMING();
    
    if(!this->texture) {
        throw std::runtime_error(std::string("TexturePNG::TexturePNG - Could not open file: ")+filename);
    }    
    SDL_QueryTexture(this->texture, &this->textureFormat, NULL, &this->width, &this->height);
    */
    this->pixelFormat=this->stbimage_texture->getSurface()->format;
    std::cout << "finished!" << std::endl;
}

void TexturePNG::convertSurfaceToTexture(){

}

void TexturePNG::lock(){
    if(SDL_LockTexture(this->texture, NULL, (void **)&this->pixels, &this->pitch))
    {
        // if return status is non-zero we have an error and want to show it here
        std::cout << "Error Locking Texture: " << SDL_GetError() << std::endl;
    }
    this->adjusted_pitch=this->pitch/this->pixelFormat->BytesPerPixel;
    this->p = (Uint32 *)(this->pixels); // cast for a pointer increments by 4 bytes.(RGBA)
    this->tex_head=this->p;
}

void TexturePNG::unlock(){
    SDL_UnlockTexture(this->texture);
}

void TexturePNG::destroyTexture(){
    //IMG_Quit();
    //SDL_FreeSurface(image);
    //SDL_DestroyTexture(this->texture);  // I don't think I need this because it's done in bittmap_font.h
}


void TexturePNG::getPixelAtUV(const float &U, const float &V, SDL_Color &col)
{
    uint32_t x, y;
    // set x based on U
    if (U>1){
        x= float(U-floor(U))*(this->width-1);
    }else if(U<0){
        x = float(U-ceil(U)+1.0f)*(this->width-1);
    }else{
        // 0 <= U <= 1
        x = U*(this->width-1);
    }

    // set y based on U
    if (V>1){
        y= (this->height-1)-(float(V-floor(V))*(this->height-1));
    }else if(V<0){
        y = (this->height-1)-(float(V-ceil(V)+1.0f)*(this->height-1));
    }else{
        // 0 <= U <= 1
        y = (this->height-1)-(V*(this->height-1));
    }    

    //this->p = this->tex_head+(this->adjusted_pitch*y)+x; // Texture Specific Method

	uint32_t* PixelData = (uint32_t*)((Uint8*)this->surface->pixels + y * this->surface->pitch + x * Bpp);  // Surface Specific Method



	// Retrieve the RGB values of the specific pixel
	//SDL_GetRGB(*p, this->pixelFormat, &col.r, &col.g, &col.b);  // Texture Specific Method
    SDL_GetRGB(*PixelData, this->surface->format, &col.r, &col.g, &col.b);  // Surface Specific Method
    //col.r = *(uint8_t*)(PixelData);
    ///col.g = *((uint8_t*)(PixelData)+1);
    //col.b = *((uint8_t*)(PixelData)+2);

	
}

void TexturePNG::getPixelAtXY(const int &x, const int &y, SDL_Color &col){
    col.r= pixel_array[x][y].r;
    col.g= pixel_array[x][y].g; 
    col.b= pixel_array[x][y].b;
    col.a= 255;
}


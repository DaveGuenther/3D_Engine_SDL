#include <iostream>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "TexturePNG.h"


TexturePNG::TexturePNG(const char* filename){
    
    uint8_t* pixels;
    int pitch;
    this->image=IMG_Load(filename);
    std::cout << filename;
    if(!this->image) {
        std::cout<<"IMG_Load: " << IMG_GetError() << image;
        //printf("IMG_Load: %s\n", IMG_GetError());
        //raise(1);
        // handle error
    }    
    image = SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_RGB24,0);
    pixels = (uint8_t*)this->image->pixels;
    pitch=0;
    pitch = image->pitch;
    Uint32 format;
    SDL_PixelFormat *pixelFormat;
    pixelFormat = this->image->format;
    Uint32 pixelPosition;
    SDL_Color this_col;
    Uint8 *r, *g, *b, *a= NULL;
    uint8_t red, green, blue, alpha=0;
    std::cout << SDL_GetPixelFormatName(pixelFormat->format)<< std::endl;
    // Get the size of the texture.
    int w, h;
    w=this->image->w;
    h=this->image->h;
    this->width=w;
    this->height=h;
    std::cout << w << ", " << h << std::endl;
    
    std::vector<SDL_Color> this_row;

    for (int i=0; i<w; i++){
        for (int j=0; j<h; j++){
            pixelPosition = j * pitch + (i*image->format->BytesPerPixel);
            red = pixels[pixelPosition];
            green = pixels[pixelPosition+1];
            blue = pixels[pixelPosition+2];

            this_row.push_back(SDL_Color({red,green,blue,alpha}));

        }
        this->pixel_array.push_back(this_row);
        this_row.clear();
    }

    std::cout << "finished initting" << std::endl;
}

void TexturePNG::destroyTexture(){
    IMG_Quit();
    SDL_FreeSurface(image);
}


void TexturePNG::getPixelAtUV(const float &U, const float &V, SDL_Color &col){
    uint32_t x = U*this->width;
    uint32_t y = V*this->height;
    
    col.r= pixel_array[x][y].r;
    col.g= pixel_array[x][y].g; 
    col.b= pixel_array[x][y].b;
    col.a= 255;
}

void TexturePNG::getPixelAtXY(const int &x, const int &y, SDL_Color &col){
    col.r= pixel_array[x][y].r;
    col.g= pixel_array[x][y].g; 
    col.b= pixel_array[x][y].b;
    col.a= 255;
}


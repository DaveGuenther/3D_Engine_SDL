#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TexturePNG.h"


TexturePNG::TexturePNG(const char* filename){
    
    uint8_t* pixels;
    int pitch;
    this->image=IMG_Load(filename);
    std::cout << filename;
    if(!this->image) {
        throw std::runtime_error(std::string("TexturePNG::TexturePNG - Could not open file: ")+filename);
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


/*void TexturePNG::getPixelAtUV(const float &U, const float &V, SDL_Color &col){
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


    
    col.r= pixel_array[x][y].r;
    col.g= pixel_array[x][y].g; 
    col.b= pixel_array[x][y].b;
    col.a= 255;
}
*/

void TexturePNG::getPixelAtSurfaceUV(const float &U, const float &V, SDL_Color &col)
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

	// Bytes per pixel
	const Uint8 Bpp = this->image->format->BytesPerPixel;

	/*
	Retrieve the address to a specific pixel
	pSurface->pixels	= an array containing the SDL_Surface' pixels
	pSurface->pitch		= the length of a row of pixels (in bytes)
	X and Y				= the offset on where on the image to retrieve the pixel, (0, 0) is in the upper left corner of the image
	*/
	Uint8* pPixel = (Uint8*)this->image->pixels + y * this->image->pitch + x * Bpp;

	Uint32 PixelData = *(Uint32*)pPixel;

	//col = {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE};

	// Retrieve the RGB values of the specific pixel
	SDL_GetRGB(PixelData, this->image->format, &col.r, &col.g, &col.b);

	
}

void TexturePNG::getPixelAtXY(const int &x, const int &y, SDL_Color &col){
    col.r= pixel_array[x][y].r;
    col.g= pixel_array[x][y].g; 
    col.b= pixel_array[x][y].b;
    col.a= 255;
}


#ifndef TEXTUREPNG_H
#define TEXTUREPNG_H

#include <vector>
#include <SDL2/SDL.h>
#include <memory>
#include "../render/Renderer_Observer.h"
#include "../3rd_party/bitmap_font.h"
/**
 * @brief This library uses SDL Surfaces to load a .png texture into memory and allow for easy pixel sampling (for use with texturemapping)
 * 
 */
class TexturePNG{
    public:
        /**
         * @brief Construct a new PNG Texture object.  Texture is initiated with a path to the .png file to load
         * 
         * @param filename 
         */
        TexturePNG(std::shared_ptr<RendererSubject> this_renderer_subject, const char* filename);
        
        /**
         * One-time function to convert SDL_Surface to SDL_Texture (with STREAMING) by writing each pixel
        */
        void convertSurfaceToTexture();
        
        
        void lock(); // Do this before referencing pixel data
        void unlock(); // do this after we are done reading pixels

        /**
         * @brief Explicit Destructor is called by TextureList class destructor.  If this method were called ~TexturePNG, it would
         * result in a seg fault because the TextureList class might be destroyed first.
         * 
         */
        void destroyTexture();

        /**
         * @brief Get the Pixel At U V location of texture sampling directly from the surface.
         * 
         * @param U floating point between 0.0 and 1.0
         * @param V floating point between 0.0 and 1.0
         * @param col Pass a color in by reference to be set from within the function
         */        
        void getPixelAtUV(const float &U, const float &V, SDL_Color &col);

        /**
         * @brief Get the Pixel At X Y location of texture.  
         * 
         * @param x int value from 0 to image->width
         * @param y int value from 0 to image->height
         * @param col Pass a color in by reference to be set from within the function
         */
        void getPixelAtXY(const int &x, const int &y, SDL_Color &col);


    private:
        int width, height;
        std::vector<std::vector<SDL_Color>> pixel_array;
        //SDL_Surface *image;
        std::shared_ptr<stbimageTexture> stbimage_texture=NULL;
        SDL_PixelFormat *pixelFormat=NULL;
        SDL_Surface *surface=NULL;        
        SDL_Texture *texture=NULL;
        Uint32 textureFormat;
        uint8_t *pixels=NULL;
        Uint32 *tex_head=NULL;
        int pitch=0;  // Size of one row of pixels in raw bytes
        Uint32 adjusted_pitch=0; // this is the pitch of a single row in pixels (not bytes)
        Uint32 *p=NULL; // this will be the pixel pointer to a specific pixel in the buffer
        Uint8 Bpp=0;
        SDL_Renderer* renderer;
        std::shared_ptr<Renderer_Observer> rendererObserver;
        //std::shared_ptr<stbimageTexture> png_image;
        
};

#endif
#ifndef TEXTUREPNG_H
#define TEXTUREPNG_H

#include <vector>
#include "SDL.h"


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
        TexturePNG(const char* filename);

        /**
         * @brief Explicit Destructor is called by TextureList class destructor.  If this method were called ~TexturePNG, it would
         * result in a seg fault because the TextureList class might be destroyed first.
         * 
         */
        void destroyTexture();

        
        /**
         * @brief Get the Pixel At U V location of texture.
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
        SDL_Surface *image;

};

#endif
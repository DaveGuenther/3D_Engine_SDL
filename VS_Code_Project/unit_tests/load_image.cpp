#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "SDL_image.h"

class Texture{
    public:
        Texture(std::string filename);
        void getPixelAtUV(const float &U, const float &V);
        void getPixelAtXY(const int &x, const int &y);

    private:
       SDL_Surface *image; 
};




int main (int argv, char** args){
    SDL_Window *window;
    SDL_Renderer *renderer;
	window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 380, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
    
    IMG_Init(IMG_INIT_PNG);
    	
    // load sample.png into image
    SDL_Surface *image;
    image=IMG_Load("colorgrid.png");
    if(!image) {
        printf("IMG_Load: %s\n", IMG_GetError());
        // handle error
    }

    // Following: https://gamedev.stackexchange.com/questions/98641/how-do-i-modify-textures-in-sdl-with-direct-pixel-access

    //SDL_Texture* ourPNG=SDL_CreateTextureFromSurface(renderer, image);
    SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_ABGR8888,0);
    uint8_t* pixels = (uint8_t*)image->pixels;
    //uint8_t* pixels = nullptr;
    int pitch=0;
    pitch = image->pitch;
    Uint32 format;
    SDL_PixelFormat *pixelFormat;
    pixelFormat = image->format;
    Uint32 pixelPosition;
    SDL_Color this_col;
    Uint8 *r, *g, *b, *a= NULL;
    uint8_t red, green, blue, alpha=0;
    std::cout << SDL_GetPixelFormatName(pixelFormat->format)<< std::endl;
    // Get the size of the texture.
    int w, h;
    w=image->w;
    h=image->h;
    std::cout << w << ", " << h << std::endl;
    std::vector<std::vector<SDL_Color>> pixel_array;
    std::vector<SDL_Color> this_row;
    //SDL_Color pixel_array[w][h];
    for (int i=0; i<=w; i++){
        for (int j=0; j<=h; j++){
            pixelPosition = j * pitch + (i*4);
            alpha = pixels[pixelPosition];
            blue = pixels[pixelPosition+1];
            green = pixels[pixelPosition+2];
            red = pixels[pixelPosition+3];
            this_row.push_back(SDL_Color({red,green,blue,alpha}));

            //SDL_GetRGBA(pixels[pixelPosition],pixelFormat,r, g, b, a);
            //std::cout << red << ", " << green << ", " << blue << ", " << alpha << std::endl;
        }
        pixel_array.push_back(this_row);
        this_row.clear();
    }
    std::cout << "finished initting" << std::endl;
    //SDL_QueryTexture(ourPNG, &format, nullptr, &w, &h);
    // Now let's make our "pixels" pointer point to the texture data.
    /*if (SDL_LockTexture(ourPNG, nullptr, (void**)&pixels, &pitch))
    {
        // If the locking fails, you might want to handle it somehow. SDL_GetError(); or something here.
    }*/
    Uint32 start_array_time, end_array_time, start_surface_time, end_surface_time=0;
    //SDL_PixelFormat pixelFormat;
    //pixelFormat.format = image->format;
    //std::cout<< "Forman Name: " << SDL_GetPixelFormatName(format) << std::endl;;
    bool game_is_running=true;
    while(game_is_running){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                game_is_running=false;
            }
        }

        
        
        SDL_RenderClear(renderer);
        start_array_time=SDL_GetTicks();
        for (int i=0; i<640; i++){
            for (int j=0;j<380; j++){
                SDL_SetRenderDrawColor(renderer,pixel_array[i][j].r, pixel_array[i][j].g, pixel_array[i][j].b, pixel_array[i][j].a);
                SDL_RenderDrawPoint(renderer,i,j);
            }
        }
        end_array_time=SDL_GetTicks();
        /*
        start_surface_time=SDL_GetTicks();
        for (int i=0; i<=w; i++){
            for (int j=0; j<=h; j++){
                pixelPosition = j * pitch + (i*4);
                //this_row.push_back(SDL_Color({red,green,blue,alpha}));
                SDL_SetRenderDrawColor(renderer,pixels[pixelPosition+3], pixels[pixelPosition+2], pixels[pixelPosition+1], pixels[pixelPosition]);
                SDL_RenderDrawPoint(renderer,i,j);
                //SDL_GetRGBA(pixels[pixelPosition],pixelFormat,r, g, b, a);
                //std::cout << red << ", " << green << ", " << blue << ", " << alpha << std::endl;
            }
        
        }
        end_surface_time=SDL_GetTicks();*/
        std::cout<< "array Time (ticks): " << end_array_time-start_array_time << "    surface Time (Ticks): " << end_surface_time-start_surface_time << std::endl;

        /*for (int px=0; px<=w/2;px++){
            for(int py=0; py<=h/2;py++){
                // Before setting the color, we need to know where we have to place it.
                pixelPosition = py * pitch + (px*pixelFormat.BytesPerPixel);
                std::cout << "pixel position: " << px << ", " << py << "   Col: " << std::endl;
                SDL_GetRGBA(pixels[pixelPosition],&pixelFormat,r, g, b, a);

                //this_col = SDL_Color(pixels[pixelPosition]);
                SDL_SetRenderDrawColor(renderer,*r, *g, *b,255);
                SDL_RenderDrawPoint(renderer,px,py);
            }
        }*/
        
        

        //SDL_RenderCopy(renderer,ourPNG, NULL, NULL);
        
        SDL_RenderPresent(renderer);


    }
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_FreeSurface(image);
    //SDL_DestroyTexture(ourPNG);
    SDL_Quit();

    return 0;
}


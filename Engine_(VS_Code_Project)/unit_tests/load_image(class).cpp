#include <iostream>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "utility/Texture.h"

/*class Texture{
    public:
        Texture(const char* filename);
        ~Texture();
        void getPixelAtUV(const float &U, const float &V, SDL_Color &col);
        void getPixelAtXY(const int &x, const int &y, SDL_Color &col);

    private:
        int width, height;
        std::vector<std::vector<SDL_Color>> pixel_array;
        SDL_Surface *image;
};

Texture::Texture(const char* filename){
    
    uint8_t* pixels;
    int pitch;
    this->image=IMG_Load(filename);
    if(!this->image) {
        printf("IMG_Load: %s\n", IMG_GetError());
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
    //SDL_Color pixel_array[w][h];
    for (int i=0; i<w; i++){
        for (int j=0; j<h; j++){
            pixelPosition = j * pitch + (i*image->format->BytesPerPixel);
            red = pixels[pixelPosition];
            green = pixels[pixelPosition+1];
            blue = pixels[pixelPosition+2];
            //alpha = pixels[pixelPosition+3];
            this_row.push_back(SDL_Color({red,green,blue,alpha}));

            //SDL_GetRGBA(pixels[pixelPosition],pixelFormat,r, g, b, a);
            //std::cout << red << ", " << green << ", " << blue << ", " << alpha << std::endl;
        }
        this->pixel_array.push_back(this_row);
        this_row.clear();
    }
    std::cout << "finished initting" << std::endl;
}

Texture::~Texture(){
    IMG_Quit();
    SDL_FreeSurface(image);
}

void Texture::getPixelAtUV(const float &U, const float &V, SDL_Color &col){
    uint32_t x = U*this->width;
    uint32_t y = V*this->height;
    
    col.r= pixel_array[x][y].r;
    col.g= pixel_array[x][y].g; 
    col.b= pixel_array[x][y].b;
    col.a= pixel_array[x][y].a;
}


void Texture::getPixelAtXY(const int &x, const int &y, SDL_Color &col){
    col.r= pixel_array[x][y].r;
    col.g= pixel_array[x][y].g; 
    col.b= pixel_array[x][y].b;
    col.a= pixel_array[x][y].a;
}

*/

int main (int argv, char** args){
    SDL_Window *window;
    SDL_Renderer *renderer;
	window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 380, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
    
    IMG_Init(IMG_INIT_PNG);

    Texture my_texture("texture16.png");



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

        
        SDL_Color col;
        SDL_RenderClear(renderer);
        start_array_time=SDL_GetTicks();
        /*for (int i=0; i<16; i++){
            for (int j=0;j<16; j++){
                my_texture.getPixelAtXY(i,j,col);
                SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
                SDL_RenderDrawPoint(renderer,i,j);
            }
        }*/

        for (float v=0;v<=1.0;v+=0.1){
            for (float u=0;u<=1.0;u+=0.1){
                my_texture.getPixelAtUV(u,v,col);
                SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
                SDL_RenderDrawPoint(renderer,u*10,v*10);
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

    //SDL_DestroyTexture(ourPNG);
    SDL_Quit();

    return 0;
}


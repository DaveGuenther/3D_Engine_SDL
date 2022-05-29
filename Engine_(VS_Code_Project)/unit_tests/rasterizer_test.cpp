#include "SDL2/SDL.h"
#include "render/Rasterizer.h"



void drawPoint(SDL_Renderer* renderer, int x, int y){

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPointF(renderer, float(x), float(y));

}

int main(int argv, char** args){
    SDL_Init(SDL_INIT_EVERYTHING);
    //Renderer* Engine_Renderer = new Renderer(640,380);
	
    SDL_Window *window;
    SDL_Renderer *renderer;
    	window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 380, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderClear(renderer);
    Vec3d v0(5.0f, 10.0f,  4.0f);
    Vec3d v1(8.0f, 2.0f, 4.0f);
    Vec3d v2(14.0f, 14.0f, 4.0f);
    
    Triangle my_tri(v0, v1, v2, 0);

    Triangle_Rasterizer my_rastered_tri(my_tri);
    std::map<int, std::map<int, int>> my_bitmap = my_rastered_tri.getBitmap();
    Vec2d bitmap_start_pos = my_rastered_tri.getBitmapStartPos();
    Vec2d bitmap_size = my_rastered_tri.getBitmapSize();
    for (int y = 0; y < bitmap_size.getY(); y++){
        for (int x = 0; x < bitmap_size.getX(); x++){
            // Draw each "true" pixel
            if (my_bitmap[x][y]==true){
                drawPoint(renderer, x+bitmap_start_pos.getX(), y+bitmap_start_pos.getY());
            }
        }
    }
    SDL_RenderPresent(renderer);
    std::cout << "Complete!" << std::endl;
    return 0;
}
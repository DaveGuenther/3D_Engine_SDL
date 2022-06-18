#ifndef TEXTURE_H
#define TEXTURE_H

class Texture{
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

#endif
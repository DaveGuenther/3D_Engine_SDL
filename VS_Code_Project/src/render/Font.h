#ifndef FONT_H
#define FONT_H

#include <memory>
#include <string>
#include "../render/Renderer_Observer.h"
#include "../3rd_party/bitmap_font.h"

class Font{
    public:
        Font(std::shared_ptr<RendererSubject> render_subject, std::string bitmap_fname, std::string csv_font_map_fname, int height_px);
        BitmapFont* getBitmapFontPtr();
    private:
        std::shared_ptr<BitmapFont> myFont;
        SDL_Renderer* renderer;
        std::shared_ptr<Renderer_Observer> rendererObserver;
};

#endif
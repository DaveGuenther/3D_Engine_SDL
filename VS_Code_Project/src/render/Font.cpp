#include <string>

#include "Font.h"
#include "../3rd_party/bitmap_font.h"

Font::Font(std::shared_ptr<RendererSubject> render_subject, std::string bitmap_fname, std::string csv_font_map_fname, int height_px){
    
    std::shared_ptr<Renderer_Observer> rendererObserver(new Renderer_Observer(*render_subject));
    this->rendererObserver=rendererObserver;
    this->renderer = this->rendererObserver->getSDLRendererPointer();
    this->myFont = std::shared_ptr<BitmapFont>(new BitmapFont(this->renderer, bitmap_fname, csv_font_map_fname, height_px));
}

BitmapFont* Font::getBitmapFontPtr(){
    return this->myFont.get();
}
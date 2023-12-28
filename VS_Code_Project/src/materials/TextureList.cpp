#include "TextureList.h"
#include "TexturePNG.h"

TextureList::TextureList(std::shared_ptr<RendererSubject> this_renderer_subject){
    this->rendererSubject = this_renderer_subject;
}

void TextureList::destroyTextureList(){
    for (auto texture:this->this_texture_list){
        texture.second.destroyTexture();
    }
}

TextureList::~TextureList(){
    destroyTextureList();
}

std::shared_ptr<TexturePNG> TextureList::insertOrAssignTexture(const std::string filename){
    std::string relative_path_file ="Textures/"+filename;
    TexturePNG this_texture(this->rendererSubject, relative_path_file.c_str());

    this->this_texture_list.insert_or_assign(filename,this_texture);
    std::unordered_map<std::string, TexturePNG>::iterator texture_element = this->this_texture_list.find(filename);
    return std::make_shared<TexturePNG>(texture_element->second); 
  
}
        


std::shared_ptr<TexturePNG> TextureList::getTextureByFilename(const std::string filename){
    std::shared_ptr<TexturePNG> this_texture_ptr;
    if (this->this_texture_list.find(filename) == this->this_texture_list.end()){
        // texture not in list
        this_texture_ptr = NULL;
    }else{
        // texture present in list
        std::unordered_map<std::string, TexturePNG>::iterator texture_element = this->this_texture_list.find(filename);
        this_texture_ptr = std::make_shared<TexturePNG>(texture_element->second);
    }
    return this_texture_ptr;
}
    
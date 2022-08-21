#include "../materials/MaterialMapper.h"
#include "../materials/MTL.h"
#include "../materials/TextureList.h"

void MaterialMapper::doMap(std::shared_ptr<MTL> MTLfile, std::shared_ptr<TextureList> texture_list){
    const std::unordered_map<std::string, std::string> MTL_map = MTLfile->getMTL_map();
    for (auto element:MTL_map){
        texture_list->insertOrAssignTexture(element.second);
    }
}
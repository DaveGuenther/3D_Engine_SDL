#ifndef MATERIALMAPPER_H
#define MATERIALMAPPER_H

#include <memory>
#include "materials/MTL.h"
#include "materials/TextureList.h"

class MaterialMapper{
    public:
        static void doMap(std::shared_ptr<MTL> MTLfile, std::shared_ptr<TextureList> texture_list);

};


#endif
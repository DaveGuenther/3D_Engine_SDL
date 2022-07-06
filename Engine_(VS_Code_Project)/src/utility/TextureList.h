#ifndef TEXTURELIST_H
#define TEXTURELIST_H

#include <memory>
#include <string>
#include <unordered_map>
#include "TexturePNG.h"


/**
 * @brief This class is responsible for encapsulating all textures used through out the engine
 * into a single object with setters and getters.  This class uses the TexturePNG class directly 
 * to load PNG images and store their contents into an unordered map.  Users will use this TextureList
 * class to obtain pointers to Texture objects to be stored with triangle data.
 * 
 */
class TextureList{
    public:
        TextureList();
        ~TextureList();
        void destroyTextureList();
        /**
         * @brief This method accepts a string of a relative filepath to a texture file.  If the 
         * texture has not already been loaded by the TextureList, it will be loaded and a pointer
         * to the Texture is returned.  Otherwise, if the filename has already been loaded by the 
         * TextureList, it will return a pointer to the Texture.
         * 
         * @param filename This is the string relative filename (e.g. 'Textures/mytexure.png')
         * @return std::shared_ptr<TexturePNG> 
         */
        std::shared_ptr<TexturePNG> insertOrAssignTexture(const std::string filename);
        
        /**
         * @brief This method will take a string filename and if that file has been loaded by the
         * TextureList, it will return a pointer to that Texture object.  Otherwise it will return
         * a null pointer.
         * 
         * @param filename 
         * @return std::shared_ptr<TexturePNG> 
         */
        std::shared_ptr<TexturePNG> getTextureByFilename(const std::string filename);
    
    private:
        /**
         * @brief unordered map with format: (string filename, Texture)
         * 
         */
        std::unordered_map<std::string, TexturePNG> this_texture_list;

};


#endif
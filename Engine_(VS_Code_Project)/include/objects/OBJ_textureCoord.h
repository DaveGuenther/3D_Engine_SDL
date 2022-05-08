#ifndef LEXLINE_TEXTURECOORD_H
#define LEXLINE_TEXTURECOORD_H

#include <string>


class OBJ_textureCoord{
    private:


    public:
        void lex(std::string thisLine);
        float getU();
        float getV();
        float getW();

        float u=0.0f;
        float v=0.0f;
        float w=0.0f;
};


#endif
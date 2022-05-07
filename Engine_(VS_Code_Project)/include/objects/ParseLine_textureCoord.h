#ifndef PARSELINE_TEXTURECOORD_H
#define PARSELINE_TEXTURECOORD_H

#include <string>


class ParseLine_textureCoord{
    private:
        float u=0.0f;
        float v=0.0f;
        float w=0.0f;

    public:
        void parse(std::string thisLine);
        float getU();
        float getV();
        float getW();
};


#endif
#ifndef LEXLINE_TEXTURECOORD_H
#define LEXLINE_TEXTURECOORD_H

#include <string>

/**
 * @brief This class will lex the tokens for a UV Coodrinate in the stringstream.
@brief This class will lex the tokens for a single line if the line starts with "t" indicating it is a texture defininition
 */
class OBJ_Lex_textureCoord{
    private:


    public:
        void lex(std::string thisLine);

        float u=0.0f;
        float v=0.0f;
        float w=0.0f;
};


#endif
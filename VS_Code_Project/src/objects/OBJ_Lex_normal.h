#ifndef LEXLINE_NORMAL_H
#define LEXLINE_NORMAL_H

#include <string>
#include "../utility/Vec3d.h"

/**
 * @brief This class will lex the tokens for a single line if the line starts with "vn" indicating it is a vector normal definition
 * 
 */
class OBJ_Lex_normal{

        

    public:
        void lex(std::string thisLine);
        Vec3d thisNormal;
        Vec3d getNormal();

    private:
};


#endif
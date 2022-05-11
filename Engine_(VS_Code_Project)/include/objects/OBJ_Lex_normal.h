#ifndef LEXLINE_NORMAL_H
#define LEXLINE_NORMAL_H

#include <string>
#include "utility/Vec3d.h"


class OBJ_Lex_normal{
    private:
        

    public:
        void lex(std::string thisLine);
        Vec3d thisNormal;
        Vec3d getNormal();

};


#endif
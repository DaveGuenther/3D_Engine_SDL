#ifndef LEXLINE_NORMAL_H
#define LEXLINE_NORMAL_H

#include <string>
#include "utility/Vec3d.h"


class LexLine_normal{
    private:
        Vec3d thisNormal;

    public:
        void lex(std::string thisLine);
        Vec3d getNormal();

};


#endif
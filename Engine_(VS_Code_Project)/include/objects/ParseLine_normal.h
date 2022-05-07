#ifndef PARSELINE_NORMAL_H
#define PARSELINE_NORMAL_H

#include <string>
#include "utility/Vec3d.h"


class ParseLine_normal{
    private:
        Vec3d thisNormal;

    public:
        void parse(std::string thisLine);
        Vec3d getNormal();

};


#endif
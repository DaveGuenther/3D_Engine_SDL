#ifndef OBJ_H
#define OBJ_H

#include <string>
#include "utility/Mesh.h"

class OBJ{
    private:
        Mesh thisMesh;
        
    public:
        OBJ(std::string filename);
        Mesh& getMesh();



};

#endif
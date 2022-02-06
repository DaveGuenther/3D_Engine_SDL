#ifndef TRIANGLE_MODIFICATIONS_PIPELINE_H
#define TRIANGLE_MODIFICATIONS_PIPELINE_H

#include <vector>
#include "Triangle_Modifier.h"

class Triangle_Modifications_Pipeline{
    private:
        std::vector<Triangle_Modifier> modifications;
    
    public:
    Triangle_Modifications_Pipeline();
    
    // These functions will be removed
    void Add_Translation(float x, float y, float z);
    void Add_Rotation(float x, float y, float z, Vec3d center);

    const std::vector<Triangle_Modifier>& getModifications();

};

#endif
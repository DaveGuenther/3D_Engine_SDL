#ifndef ROTATOR_SERVICE_H
#define ROTATOR_SERVICE_H

#include "Mesh_Pipeline.h"
#include "Mat4x4.h"

class Rotator_Service {
    public: 
        static void Rotate_Pipeline(Mesh_Pipeline &this_mesh_pipeline);

    private:
        static Mat4x4 Calculate_Rotation_Z_Matrix(float fTheta, float tTheta);
        static Mat4x4 Calculate_Rotation_X_Matrix(float fTheta, float tTheta);
        
};
#endif
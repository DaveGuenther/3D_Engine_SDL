#ifndef TRIANGLE_MODIFIER_H
#define TRIANGLE_MODIFIER_H
#include <iostream>
#include "Vec3d.h"
#include "Triangle.h"
#include "Mat4x4.h"

class Triangle_Modifier{
    public: 
        virtual void ModifyTri(Triangle &tri)=0;

};

class Rotator: public Triangle_Modifier{
    private:
        float x_degs;
        float z_degs;
        Vec3d center_of_rotation;
        Mat4x4 mat_XRot;
        Mat4x4 mat_ZRot;
    public:
        Rotator(float x_degrees, float z_degrees, Vec3d center);
        void ModifyTri(Triangle &tri);

};

class Translator: public Triangle_Modifier{
    private:
        float x_dist;
        float z_dist;
    public:
        Translator(float x_distance, float z_distance);
        void ModifyTri(Triangle &tri);

};

#endif
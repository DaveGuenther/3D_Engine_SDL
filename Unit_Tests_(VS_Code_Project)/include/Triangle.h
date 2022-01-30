#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Vec3d.h"

class Triangle{
    public:
        Vec3d p[3];
        Triangle();
        Triangle(Vec3d pt1, Vec3d pt2, Vec3d pt3);
    
};

#endif
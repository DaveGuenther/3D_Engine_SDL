#include "Triangle.h"

Triangle::Triangle(){

    p[0]=Vec3d{0, 0, 0};
    p[1]=Vec3d{0, 0, 0};
    p[2]=Vec3d{0, 0, 0};

}

Triangle::Triangle(Vec3d pt1, Vec3d pt2, Vec3d pt3){
    p[0]=pt1;
    p[1]=pt2;
    p[2]=pt3;
}
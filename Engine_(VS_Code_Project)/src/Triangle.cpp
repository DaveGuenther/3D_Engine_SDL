#include "Triangle.h"

Triangle::Triangle(){

    p[0]=Vec3d(0, 0, 0);
    p[1]=Vec3d(0, 0, 0);
    p[2]=Vec3d(0, 0, 0);

}

Triangle::Triangle(const Vec3d &pt1, const Vec3d &pt2, const Vec3d &pt3){
    p[0]=pt1;
    p[1]=pt2;
    p[2]=pt3;
}

Triangle::Triangle (const Triangle &T){
    p[0]=T.p[0];
    p[1]=T.p[1];
    p[2]=T.p[2];
}

void Triangle::setTrianglePoint(int point, const Vec3d &vec){
    p[point]=vec;
}

std::string Triangle::toString(){
    std::string point1 = p[0].toString();
    std::string point2 = p[1].toString();
    std::string point3 = p[2].toString();
    std::string ret_val = "Triangle(" + point1 + ", " + point2 + ", " + point3 + ")";
    return ret_val;
}

Vec3d Triangle::getTrianglePoint(int point){
    return p[point];
}
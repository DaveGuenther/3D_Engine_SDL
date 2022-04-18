#include "utility/Triangle.h"
#include "utility/Vector_Math_Service.h"

Triangle::Triangle(){

    p[0]=Vec3d(0, 0, 0);
    p[1]=Vec3d(0, 0, 0);
    p[2]=Vec3d(0, 0, 0);
    this->tri_id=0;
    color.r=255; color.g=255; color.b=255; color.a = 255;

}

Triangle::Triangle(const Vec3d &pt1, const Vec3d &pt2, const Vec3d &pt3, const int &triangle_id, const SDL_Color this_color){
    p[0]=pt1;
    p[1]=pt2;
    p[2]=pt3;
    tri_id=triangle_id;    
    color = this_color;
}

Triangle::Triangle (const Triangle &T){
    p[0]=T.p[0];
    p[1]=T.p[1];
    p[2]=T.p[2];
    tri_id = T.tri_id;
    this->color = T.color;
}

void Triangle::setTrianglePoint(int point, const Vec3d &vec){
    p[point]=vec;
}

void Triangle::setID(int this_tri_id){
    tri_id=this_tri_id;
}

const SDL_Color Triangle::getColor(){
    return this->color;
}

void Triangle::setColor(SDL_Color this_color){
    this->color = this_color;
}

std::string Triangle::toString(){
    std::string point1 = p[0].toString();
    std::string point2 = p[1].toString();
    std::string point3 = p[2].toString();
    std::string ret_val = "Triangle ID=" + std::to_string(tri_id) + " (" + point1 + ", " + point2 + ", " + point3 + ")";
    return ret_val;
}

Vec3d Triangle::getTrianglePoint(int point){
    return p[point];
}

const float Triangle::getDistanceToCamera(Vec3d camera_pos){
    return VectorMathService::getVectorLength(this->getTriangleCenter()-camera_pos);
}

const float Triangle::getTriangleZCenter(){
    return (this->p[0].getZ()+ this->p[1].getZ() + this->p[2].getZ())/3.0f;
}

const float Triangle::getTriangleYCenter(){
    return (this->p[0].getY()+ this->p[1].getY() + this->p[2].getY())/3.0f;
}

const float Triangle::getTriangleXCenter(){
    return (this->p[0].getX()+ this->p[1].getX() + this->p[2].getX())/3.0f;
}

const Vec3d Triangle::getTriangleCenter(){
    return Vec3d(this->getTriangleXCenter(), this->getTriangleYCenter(), this->getTriangleZCenter());
}
#include <memory>
#include <unordered_map>
#include "Triangle.h"
#include "Vector_Math_Service.h"
#include "../materials/TexturePNG.h"

Triangle::Triangle(){
    p[0]=std::make_unique<Vec3d>(0.0f, 0.0f, 0.0f);
    p[1]=std::make_unique<Vec3d>(0.0f, 0.0f, 0.0f);
    p[2]=std::make_unique<Vec3d>(0.0f, 0.0f, 0.0f);
    
    //p[0]=Vec3d(0.0f, 0.0f, 0.0f);
    //p[1]=Vec3d(0.0f, 0.0f, 0.0f);
    //p[2]=Vec3d(0.0f, 0.0f, 0.0f);
    textureCoords[0] = Vec2d(0.0f, 0.0f);
    textureCoords[1] = Vec2d(0.0f, 0.0f);
    textureCoords[2] = Vec2d(0.0f, 0.0f);
    this->tri_id=0;
    color.r=255; color.g=255; color.b=255; color.a = 255;
    this->dim_amount=1.0f;

}

Triangle::Triangle(const Vec3d &pt1, const Vec3d &pt2, const Vec3d &pt3, const int &triangle_id){
    p[0]=std::make_unique<Vec3d>(pt1.x, pt1.y, pt1.z);
    p[1]=std::make_unique<Vec3d>(pt2.x, pt2.y, pt2.z);
    p[2]=std::make_unique<Vec3d>(pt3.x, pt3.y, pt3.z);

    //p[0]=pt1;
    //p[1]=pt2;
    //p[2]=pt3;
    tri_id=triangle_id;    
    color = SDL_Color {255, 0, 255, 255};
    this->dim_amount=1.0f;
}

Triangle::Triangle(const Vec3d &pt1, const Vec3d &pt2, const Vec3d &pt3, const int &triangle_id, const SDL_Color this_color){
    p[0]=std::make_unique<Vec3d>(pt1.x, pt1.y, pt1.z);
    p[1]=std::make_unique<Vec3d>(pt2.x, pt2.y, pt2.z);
    p[2]=std::make_unique<Vec3d>(pt3.x, pt3.y, pt3.z);
    
    //p[0]=pt1;
    //p[1]=pt2;
    //p[2]=pt3;
    tri_id=triangle_id;    
    color = this_color;
    this->dim_amount=1.0f;
}

Triangle::Triangle(const Vec3d &pt1, const Vec3d &pt2, const Vec3d &pt3, const Vec2d &tex_p1, const Vec2d &tex_p2, const Vec2d &tex_p3, const int &triangle_id, const SDL_Color this_color, const float dim_amount, std::shared_ptr<TexturePNG> this_texture_ptr){
    p[0]=std::make_unique<Vec3d>(pt1.x, pt1.y, pt1.z);
    p[1]=std::make_unique<Vec3d>(pt2.x, pt2.y, pt2.z);
    p[2]=std::make_unique<Vec3d>(pt3.x, pt3.y, pt3.z);

    //p[0]=pt1;
    //p[1]=pt2;
    //p[2]=pt3;
    this->textureCoords[0]=tex_p1;
    this->textureCoords[1]=tex_p2;
    this->textureCoords[2]=tex_p3;
    tri_id=triangle_id;    
    color = SDL_Color {255, 0, 255, 255};
    this->texture_ptr=this_texture_ptr;
    this->dim_amount=dim_amount;
}

Triangle::Triangle (const Triangle &T){

    p[0]=std::make_unique<Vec3d>(*(T.p[0]));
    p[1]=std::make_unique<Vec3d>(*(T.p[1]));
    p[2]=std::make_unique<Vec3d>(*(T.p[2]));

    tri_id = T.tri_id;
    this->color = T.color;
    this->textureCoords[0] = T.textureCoords[0];
    this->textureCoords[1] = T.textureCoords[1];
    this->textureCoords[2] = T.textureCoords[2];
    this->texture_ptr=T.texture_ptr;  // Careful changing this to a unique_ptr!  It's used by MANY triangles
    this->dim_amount=T.dim_amount;
    
}

Triangle Triangle::operator=(const Triangle &T){

    Triangle this_tri;
    this_tri.p[0]=std::make_unique<Vec3d>(*(T.p[0]));
    this_tri.p[1]=std::make_unique<Vec3d>(*(T.p[1]));
    this_tri.p[2]=std::make_unique<Vec3d>(*(T.p[2]));

    this_tri.tri_id = T.tri_id;
    this_tri.color = T.color;
    this_tri.textureCoords[0] = T.textureCoords[0];
    this_tri.textureCoords[1] = T.textureCoords[1];
    this_tri.textureCoords[2] = T.textureCoords[2];
    this_tri.texture_ptr=T.texture_ptr;  // Careful changing this to a unique_ptr!  It's used by MANY triangles
    this_tri.dim_amount=T.dim_amount;    
    return this_tri;
}

void Triangle::setTrianglePoint(int point, const Vec3d &vec){


    p[point]=std::make_unique<Vec3d>(vec.x, vec.y, vec.z);
}

void Triangle::setUVPoint(int point, const Vec2d &vec){
    this->textureCoords[point]=vec;
    
}

void Triangle::setTexture(std::shared_ptr<TexturePNG> texture){
    this->texture_ptr=texture;
}

void Triangle::setID(int this_tri_id){
    tri_id=this_tri_id;
}

const SDL_Color& Triangle::getColor(){
    return this->color;
}

const int Triangle::getID(){
    return this->tri_id;
}

std::shared_ptr<TexturePNG> Triangle::getTexture(){
    return this->texture_ptr;
}

void Triangle::setColor(SDL_Color this_color){
    this->color = this_color;
}



void Triangle::setUnitNormalFromPoints(){
// Generate triangle normal in view space
    Vec3d viewline1 = *p[1]-*p[0];
    Vec3d viewline2 = *p[2]-*p[1];
    
    this->unit_normal_vector = VectorMathService::crossProduct(viewline1, viewline2);
    VectorMathService::getUnitVector(this->unit_normal_vector);		    
}

void Triangle::setLightDimAmount(float lightDim){
    this->dim_amount=lightDim;
}

const float& Triangle::getLightDimAmount(){
    return this->dim_amount;
}

const Vec3d& Triangle::getUnitNormalVector(){
    return this->unit_normal_vector;
}


const std::string Triangle::toString(){
    std::string point1 = p[0]->toString();
    std::string point2 = p[1]->toString();
    std::string point3 = p[2]->toString();
    std::string ret_val = "Triangle ID=" + std::to_string(tri_id) + " (" + point1 + ", " + point2 + ", " + point3 + ")";
    return ret_val;
}

const Vec3d& Triangle::getTrianglePoint(int point){
    return *p[point];
}
const Vec2d& Triangle::getUVPoint(int point){
    return textureCoords[point];
}


const float Triangle::getDistanceToCamera(Vec3d camera_pos){
    return VectorMathService::getVectorLength(this->getTriangleCenter()-camera_pos);
}

const float Triangle::getTriangleZCenter(){
    return (this->p[0]->z+ this->p[1]->z + this->p[2]->z)/3.0f;
}

const float Triangle::getTriangleYCenter(){
    return (this->p[0]->y+ this->p[1]->y + this->p[2]->y)/3.0f;
}

const float Triangle::getTriangleXCenter(){
    return (this->p[0]->x+ this->p[1]->x + this->p[2]->x)/3.0f;
}

const Vec3d Triangle::getTriangleCenter(){
    return Vec3d(this->getTriangleXCenter(), this->getTriangleYCenter(), this->getTriangleZCenter());
}
#include "math.h"
#include "utility/Vector_Math_Service.h"
#include "utility/Vec3d.h"

float VectorMathService::dotProduct(const Vec3d& A, const Vec3d& B){
    return (A.getX()*B.getX())+(A.getY()*B.getY())+(A.getZ()*B.getZ());
}

Vec3d VectorMathService::crossProduct(const Vec3d& A, const Vec3d& B){
    return Vec3d(((A.getY()*B.getZ()) - (A.getZ()*B.getY())), ((A.getZ()*B.getX()) - (A.getX()*B.getZ())), ((A.getX()*B.getY()) - (A.getY()*B.getX())));
}

float VectorMathService::getVectorLength(const Vec3d& this_vec){
    return sqrt((this_vec.getX()*this_vec.getX())+(this_vec.getY()*this_vec.getY())+(this_vec.getZ()*this_vec.getZ()));
}

void VectorMathService::getUnitVector(Vec3d& this_vec){
    float vector_length = getVectorLength(this_vec);
    this_vec.setX(this_vec.getX()/vector_length);
    this_vec.setY(this_vec.getY()/vector_length);
    this_vec.setZ(this_vec.getZ()/vector_length);
}


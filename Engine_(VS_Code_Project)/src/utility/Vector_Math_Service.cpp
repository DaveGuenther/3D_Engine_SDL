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

void VectorMathService::MultiplyMatrixVector(Vec3d &i, Vec3d &o, const Mat4x4 &m){

    //[x, y, z, 1] * mat4x4 gives us 1x4 vector
	o.setX(float(i.getX()) * m.m[0][0] + i.getY() * m.m[1][0] + i.getZ() * m.m[2][0] + 1*m.m[3][0]);
	o.setY(i.getX() * m.m[0][1] + i.getY() * m.m[1][1] + i.getZ() * m.m[2][1] + 1*m.m[3][1]);
	o.setZ(i.getX() * m.m[0][2] + i.getY() * m.m[1][2] + i.getZ() * m.m[2][2] + 1*m.m[3][2]);
	float w = i.getX() * m.m[0][3] + i.getY() * m.m[1][3] + i.getZ() * m.m[2][3] + 1*m.m[3][3];


	// Convert from 1x4 to 1x3 matrix
	if (w!=0)
	{
		o.setX(o.getX()/w);
		o.setY(o.getY()/w);
		o.setZ(o.getZ()/w);
	}
}

Vec3d VectorMathService::vectorIntersectPlane(Vec3d &plane_p, Vec3d &plane_n, Vec3d &lineStart, Vec3d &lineEnd){
    getUnitVector(plane_n);
    float plane_d = -dotProduct(plane_n, plane_p);
    float ad = dotProduct(lineStart, plane_n);
    float bd = dotProduct(lineEnd, plane_n);
    float t = (-plane_d - ad) / (bd - ad);
    Vec3d lineStartToEnd = lineEnd - lineStart;
    Vec3d lineToIntersect = t * lineStartToEnd;
    return lineStart + lineToIntersect;

}
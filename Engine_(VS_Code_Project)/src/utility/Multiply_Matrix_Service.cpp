#include "utility/Multiply_Matrix_Service.h"

void Multiply_Matrix_Service::MultiplyMatrixVector(Vec3d &i, Vec3d &o, const Mat4x4 &m){

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



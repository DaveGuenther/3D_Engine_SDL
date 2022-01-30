#include "Multiply_Matrix_Service.h"

void Multiply_Matrix_Service::MultiplyMatrixVector(Vec3d &i, Vec3d &o, Mat4x4 &m){
	
    //[x, y, z, 1] * mat4x4 gives us 1x4 vector
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + 1*m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + 1*m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + 1*m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + 1*m.m[3][3];


	// Convert from 1x4 to 1x3 matrix
	if (w!=0)
	{
		o.x=o.x/w;
		o.y=o.y/w;
		o.z=o.z/w;
	}
}
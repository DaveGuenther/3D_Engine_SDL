#include <iostream>

#include "math.h"
#include "Vector_Math_Service.h"
#include "Vec3d.h"
#include "Triangle.h"

float VectorMathService::dotProduct(const Vec3d& A, const Vec3d& B){
    return (A.x*B.x)+(A.getY()*B.getY())+(A.getZ()*B.getZ());
}

Vec3d VectorMathService::crossProduct(const Vec3d& A, const Vec3d& B){
    return Vec3d(((A.getY()*B.getZ()) - (A.getZ()*B.getY())), ((A.getZ()*B.x) - (A.x*B.getZ())), ((A.x*B.getY()) - (A.getY()*B.x)));
}

float VectorMathService::getVectorLength(const Vec3d& this_vec){
    return sqrt((this_vec.x*this_vec.x)+(this_vec.getY()*this_vec.getY())+(this_vec.getZ()*this_vec.getZ()));
}

void VectorMathService::getUnitVector(Vec3d& this_vec){
    float vector_length = getVectorLength(this_vec);
    this_vec.x= this_vec.x/vector_length;
    this_vec.setY(this_vec.getY()/vector_length);
    this_vec.setZ(this_vec.getZ()/vector_length);
}

Vec3d VectorMathService::MultiplyMatrixVector( const Mat4x4 &m, Vec3d &i){
    Vec3d v;
    v.x=i.x*m.m[0][0] + i.getY()*m.m[1][0] + i.getZ()*m.m[2][0] + i.getW() * m.m[3][0];
    v.setY(i.x*m.m[0][1] + i.getY()*m.m[1][1] + i.getZ()*m.m[2][1] + i.getW() * m.m[3][1]);
    v.setZ(i.x*m.m[0][2] + i.getY()*m.m[1][2] + i.getZ()*m.m[2][2] + i.getW() * m.m[3][2]);
    v.setW(i.x*m.m[0][3] + i.getY()*m.m[1][3] + i.getZ()*m.m[2][3] + i.getW() * m.m[3][3]);
    return v;
}


Vec3d VectorMathService::vectorIntersectPlane(Vec3d &plane_p, Vec3d &plane_n, Vec3d &lineStart, Vec3d &lineEnd, float &alpha){
    getUnitVector(plane_n);
    float plane_d = -dotProduct(plane_n, plane_p);
    float ad = dotProduct(lineStart, plane_n);
    float bd = dotProduct(lineEnd, plane_n);
    alpha = (-plane_d - ad) / (bd - ad);  //t is the alpha value between lineStart and lineEnd (use for lerping!)
	// send t back for UV clipping, or define the new UV point here.
    Vec3d lineStartToEnd = lineEnd - lineStart;
    Vec3d lineToIntersect = alpha * lineStartToEnd;  
    return lineStart + lineToIntersect;

}

float VectorMathService::getSignedShortestDist(Vec3d& plane_p, Vec3d& plane_n, Vec3d& point1){
	Vec3d n = point1;
	VectorMathService::getUnitVector(n);
	return (plane_n.x * point1.x + plane_n.getY() * point1.getY() + plane_n.getZ() * point1.getZ() - VectorMathService::dotProduct(plane_n, plane_p));
}

int VectorMathService::clipTriangleWithPlane(Vec3d plane_p, Vec3d plane_n, Triangle &in_tri, Triangle &out_tri1, Triangle &out_tri2)
{
	// Make sure plane normal is indeed normal
	VectorMathService::getUnitVector(plane_n);


	// Create two temporary storage arrays to classify points either side of plane
	// If distance sign is positive, point lies on "inside" of plane
	Vec3d* inside_points[3];  int nInsidePointCount = 0;
	Vec2d* inside_UVs[3];
	Vec3d* outside_points[3]; int nOutsidePointCount = 0;
	Vec2d* outside_UVs[3];

	// Get signed distance of each point in triangle to plane
	//float d0 = dist(in_tri.getTrianglePoint(0));
	Vec3d p0= in_tri.getTrianglePoint(0);
	float d0 = VectorMathService::getSignedShortestDist(plane_p, plane_n, p0);

	Vec3d p1= in_tri.getTrianglePoint(1);
	float d1 = VectorMathService::getSignedShortestDist(plane_p, plane_n, p1);

	Vec3d p2= in_tri.getTrianglePoint(2);
	float d2 = VectorMathService::getSignedShortestDist(plane_p, plane_n, p2);	
	
	//float d1 = dist(in_tri.getTrianglePoint(1));
	//float d2 = dist(in_tri.getTrianglePoint(2));

	Vec3d in_tri_p0 = in_tri.getTrianglePoint(0); // duplicate with p0?
	Vec3d in_tri_p1 = in_tri.getTrianglePoint(1);
	Vec3d in_tri_p2 = in_tri.getTrianglePoint(2);

	Vec2d in_tri_UV0 = in_tri.getUVPoint(0);
	Vec2d in_tri_UV1 = in_tri.getUVPoint(1);
	Vec2d in_tri_UV2 = in_tri.getUVPoint(2);

	if (d0 >= 0) { 
		inside_points[nInsidePointCount] = &(in_tri_p0);
		inside_UVs[nInsidePointCount] = &(in_tri_UV0); 
		nInsidePointCount++;
	} else { 
		outside_points[nOutsidePointCount] = &(in_tri_p0);
		outside_UVs[nOutsidePointCount]=&(in_tri_UV0); 
		nOutsidePointCount++;
	}
	if (d1 >= 0) { 
		inside_points[nInsidePointCount] = &in_tri_p1;
		inside_UVs[nInsidePointCount]=&(in_tri_UV1); 
		nInsidePointCount++;
	} else { 
		outside_points[nOutsidePointCount] = &in_tri_p1;
		outside_UVs[nOutsidePointCount]=&in_tri_UV1;
		nOutsidePointCount++;
	}
	if (d2 >= 0) { 
		inside_points[nInsidePointCount] = &in_tri_p2;
		inside_UVs[nInsidePointCount]=&in_tri_UV2;
		nInsidePointCount++;
	} else { 
		outside_points[nOutsidePointCount] = &in_tri_p2;
		outside_UVs[nOutsidePointCount]=&in_tri_UV2;
		nOutsidePointCount++;
	}

	// Now classify triangle points, and break the input triangle into 
	// smaller output triangles if required. There are four possible
	// outcomes...

	if (nInsidePointCount == 0)
	{
		// All points lie on the outside of plane, so clip whole triangle
		// It ceases to exist

		return 0; // No returned triangles are valid
	}

	if (nInsidePointCount == 3)
	{
		// All points lie on the inside of plane, so do nothing
		// and allow the triangle to simply pass through
		out_tri1 = in_tri;

		return 1; // Just the one returned original triangle is valid
	}

	if (nInsidePointCount == 1 && nOutsidePointCount == 2)
	{
		// Triangle should be clipped. As two points lie outside
		// the plane, the triangle simply becomes a smaller triangle

		// Copy appearance info to new triangle
		out_tri1.setColor(SDL_Color {0,0,255,255});
		out_tri1.setTexture(in_tri.getTexture());
		out_tri1.setID(in_tri.getID());
		//out_tri1.col =  in_tri.col;
		//out_tri1.sym = in_tri.sym;

		// The inside point is valid, so keep that...
		out_tri1.setTrianglePoint(0, *(inside_points[0]));
		out_tri1.setUVPoint(0,*(inside_UVs[0]));

		// but the two new points are at the locations where the 
		// original sides of the triangle (lines) intersect with the plane
		float alpha1, alpha2=0.0f;
		out_tri1.setTrianglePoint(1,VectorMathService::vectorIntersectPlane(plane_p, plane_n, *(inside_points[0]), *(outside_points[0]), alpha1));
		out_tri1.setTrianglePoint(2,VectorMathService::vectorIntersectPlane(plane_p, plane_n, *(inside_points[0]), *(outside_points[1]), alpha2));


		// Perform lerp over UV Coordinates here
		Vec2d UV1 = *(inside_UVs[0]) + alpha1*(*(outside_UVs[0])-*(inside_UVs[0]));
		out_tri1.setUVPoint(1,UV1);

		Vec2d UV2 = *(inside_UVs[0]) + alpha2*(*(outside_UVs[1])-*(inside_UVs[0]));
		out_tri1.setUVPoint(2,UV2);		
		/*if (in_tri.getID()==0){
			std::cout << "UV1: " << UV1.toString() << "     UV2: " << UV2.toString() << std::endl; 
		}*/



		return 1; // Return the newly formed single triangle
	}

	if (nInsidePointCount == 2 && nOutsidePointCount == 1)
	{
		// Triangle should be clipped. As two points lie inside the plane,
		// the clipped triangle becomes a "quad". Fortunately, we can
		// represent a quad with two new triangles

		// Copy appearance info to new triangles
		
		out_tri1.setColor(SDL_Color {0,255,0,255});
		out_tri1.setID(in_tri.getID());
		out_tri1.setTexture(in_tri.getTexture());
		//out_tri1.sym = in_tri.sym;

		out_tri2.setColor(SDL_Color {255,0,0,255});
		out_tri2.setID(in_tri.getID());
		out_tri2.setTexture(in_tri.getTexture());
		//out_tri2.sym = in_tri.sym;

		float alpha_tri1_point2, alpha_tri2_point2=0.0f;

		// The first triangle consists of the two inside points and a new
		// point determined by the location where one side of the triangle
		// intersects with the plane
		out_tri1.setTrianglePoint(0, *(inside_points[0]));
		out_tri1.setTrianglePoint(1, *(inside_points[1]));
		out_tri1.setTrianglePoint(2, VectorMathService::vectorIntersectPlane(plane_p, plane_n, *(inside_points[0]), *(outside_points[0]), alpha_tri1_point2));

		// Determine UV Coords:
		out_tri1.setUVPoint(0,*(inside_UVs[0]));
		out_tri1.setUVPoint(1,*(inside_UVs[1]));
		
		// Perform lerp over UV Coordinates here
		Vec2d tri1_UV2 = *(inside_UVs[0]) + alpha_tri1_point2*(*(outside_UVs[0])-*(inside_UVs[0]));
		out_tri1.setUVPoint(2,tri1_UV2);		


		// The second triangle is composed of one of he inside points, a
		// new point determined by the intersection of the other side of the 
		// triangle and the plane, and the newly created point above
		out_tri2.setTrianglePoint(0, *(inside_points[1]));
		out_tri2.setTrianglePoint(1, out_tri1.getTrianglePoint(2));
		out_tri2.setTrianglePoint(2, VectorMathService::vectorIntersectPlane(plane_p, plane_n, *(inside_points[1]), *(outside_points[0]), alpha_tri2_point2));

		// Determine UV Coords:
		out_tri2.setUVPoint(0,*(inside_UVs[1]));
		out_tri2.setUVPoint(1,out_tri1.getUVPoint(2));
		
		// Perform lerp over UV Coordinates here
		Vec2d tri2_UV2 = *(inside_UVs[1]) + alpha_tri2_point2*(*(outside_UVs[0])-*(inside_UVs[1]));
		out_tri2.setUVPoint(2,tri2_UV2);	

		// These lines are used to test UVs
		//if (in_tri.getID()==1){
		//	std::cout << "TRI1  UV0: " << (*(inside_UVs[0])).toString() << "     UV1: " << (*(inside_UVs[1])).toString() << "     UV2: " << tri1_UV2.toString() << std::endl; 
		//	std::cout << "TRI2  UV0: " << (*(inside_UVs[1])).toString() << "     UV1: " << tri1_UV2.toString() << "     UV2: " << tri2_UV2.toString() << std::endl; 
		//
		//}

		return 2; // Return two newly formed triangles which form a quad
	}
	return 0;
}
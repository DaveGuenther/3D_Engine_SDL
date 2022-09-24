#ifndef VECTOR_MATH_SERVICE_H
#define VECTOR_MATH_SERVICE_H

#include "../utility/Triangle.h"
#include "../utility/Vec3d.h"
#include "Mat4x4.h"

class VectorMathService{
    public:
        /**
         * @brief This static method calculates the dot product of vectors A and B
         * 
         * @param A 
         * @param B 
         * @return float 
         */
        static float dotProduct(const Vec3d& A, const Vec3d& B);

        /**
         * @brief This static method calculates the cross product of vectors A and B
         * 
         * @param A 
         * @param B 
         * @return Vec3d of the Cross Product
         */
        static Vec3d crossProduct(const Vec3d& A, const Vec3d& B);

        /**
         * @brief this static method uses the pythagorean theorem to get the length of a vector.  Used as an intermediate calculation for converting a vector to a unit vector
         * 
         * @param this_vec 
         * @return float 
         */
        static float getVectorLength(const Vec3d& this_vec);

        /**
         * @brief this static method converts a standard vector into a unit vector.  To save compute time, the calculation is applied to this_vec in place
         * 
         * @param this_vec this is a non-const Vec3d& on purpose to change the object in place
         */
        static void getUnitVector(Vec3d& this_vec);

        /**
         * @brief This function will accept Vec3d &i, multiply it by Mat4x4 &m, reduce the result back to a Vec3d and stores the result in Vec3d &o.  
         * 
         * @param i This is a reference to the input Vec3d
         * @param o This is a reference to the output Vec3d.  For this function we won't return the value, but instead we'll modify the data directly from the reference. 
         * @param m This is the 4x4 Matrix that we'll use to multiply by the input vector i.  Mat4x4 could be a projetion matrix, rotation matrix, or translation matrix.
         */        
        //static void MultiplyMatrixVector(Vec3d &i, Vec3d &o, const Mat4x4 &m);

        static Vec3d MultiplyMatrixVector( const Mat4x4 &m, Vec3d &i);
        
        


        static int clipTriangleWithPlane(Vec3d plane_p, Vec3d plane_n, Triangle &in_tri, Triangle &out_tri1, Triangle &out_tri2);

        private:
            static float getSignedShortestDist(Vec3d& plane_p, Vec3d& plane_n, Vec3d& point1);

        /**
         * @brief Test and return the point where a line intersects with a plane.  
         * Taken from the javidx video: https://www.youtube.com/watch?v=HXSuNxpCzdM&t=1095s
         * 
         * @param plane_p a point on the plane
         * @param plane_n normal to the plane
         * @param lineStart starting point of a line to intersect
         * @param lineEnd ending point of a line to intersect with a plane
         * @return Vec3d returns a point where the line crosses the plane if it does in fact cross the plane, otherwise it returns the line start point
         */
        static Vec3d vectorIntersectPlane(Vec3d &plane_p, Vec3d &plane_n, Vec3d &lineStart, Vec3d &lineEnd, float &alpha);
};

#endif
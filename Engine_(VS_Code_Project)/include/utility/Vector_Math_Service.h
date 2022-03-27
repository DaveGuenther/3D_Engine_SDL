#ifndef VECTOR_MATH_SERVICE_H
#define VECTOR_MATH_SERVICE_H

#include "utility/Vec3d.h"

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
        
};

#endif
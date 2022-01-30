#ifndef MULTIPLY_MATRIX_SERVICE_H
#define MULTIPLY_MATRIX_SERVICE_H

#include "Vec3d.h"
#include "Mat4x4.h"

/**
 * @brief This class will be used for matrix multiplication
 * 
 */
class Multiply_Matrix_Service {
    public:
    /**
     * @brief This function will accept Vec3d &i, multiply it by Mat4x4 &m, reduce the result back to a Vec3d and stores the result in Vec3d &o.  
     * 
     * @param i This is a reference to the input Vec3d
     * @param o This is a reference to the output Vec3d.  For this function we won't return the value, but instead we'll modify the data directly from the reference. 
     * @param m This is the 4x4 Matrix that we'll use to multiply by the input vector i.  Mat4x4 could be a projetion matrix, rotation matrix, or translation matrix.
     */
    static void MultiplyMatrixVector(Vec3d &i, Vec3d &o, const Mat4x4 &m);
};

#endif
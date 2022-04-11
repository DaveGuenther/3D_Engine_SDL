#ifndef MAT4x4_H
#define MAT4x4_H
#include <string>

/**
 * @brief This just holds a 4x4 matrix and is used to house the rotation, translation, and projection matrices
 * 
 */
class Mat4x4{
	public: 
		float m[4][4];
		Mat4x4();
		Mat4x4(const Mat4x4 &m);  // Copy constructor

        /**
         * @brief Created an identity matrix 
         * 
         * @return Mat4x4 
         */
        static Mat4x4 matrixMakeIdentify();

		static Mat4x4 matrixMakeRotationX(float x_degs);
		static Mat4x4 matrixMakeRotationY(float y_degs);
		static Mat4x4 matrixMakeRotationZ(float z_degs);
		static Mat4x4 matrixMakeTranslation(float x, float y, float z);
		static Mat4x4 matrixMakeProjection(float fFOV, int SCREEN_W, int SCREEN_H, float fNear, float fFar);
		static Mat4x4 matrixMatrixMultiplication(Mat4x4& m1, Mat4x4& m2);



		std::string toString();
};		


#endif
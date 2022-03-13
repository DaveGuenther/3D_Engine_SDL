#include <iostream>
#include <SDL2/SDL.h>
#include "Mat4x4.h"
#include "Multiply_Matrix_Service.h"

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    int SCREEN_W = 640;
    int SCREEN_H = 360;

    Mat4x4 matProj;

        // Projection Matrix
    float fNear;
    float fFar;
    float fFOV;
    float fAspectRatio;
    float fFOV_rad;

    fNear = 0.1f;
	fFar = 1000.0f;
	fFOV=90.0f;
	fAspectRatio = (float)SCREEN_H/(float)SCREEN_W;
	fFOV_rad = 1.0/(SDL_tanf((fFOV/2)*(3.14159265f/180.0f)));

    matProj.m[0][0] = fAspectRatio*fFOV_rad;
	matProj.m[1][0] = 0.0;
	matProj.m[2][0] = 0.0;
	matProj.m[3][0] = 0.0;
	matProj.m[0][1] = 0.0;
	matProj.m[1][1] = fFOV_rad;
	matProj.m[2][1] = 0.0;
	matProj.m[3][1] = 0.0;
	matProj.m[0][2] = 0.0;
	matProj.m[1][2] = 0.0;
	matProj.m[2][2] = fFar/(fFar-fNear);
	matProj.m[3][2] = (-fFar*fNear)/(fFar-fNear);
	matProj.m[0][3] = 0.0;
	matProj.m[1][3] = 0.0;
	matProj.m[2][3] = 1.0;
	matProj.m[3][3] = 0.0;


	Mat4x4 test_4x4;
	test_4x4.m[0][0]=1;
    test_4x4.m[0][1]=2;
    test_4x4.m[0][2]=3;
    test_4x4.m[0][3]=4;
	test_4x4.m[1][0]=1;
    test_4x4.m[1][1]=2;
    test_4x4.m[1][2]=3;
    test_4x4.m[1][3]=4;
    test_4x4.m[2][0]=1;
    test_4x4.m[2][1]=2;
    test_4x4.m[2][2]=3;
    test_4x4.m[2][3]=4;
    test_4x4.m[3][0]=1;
    test_4x4.m[3][1]=2;
    test_4x4.m[3][2]=3;
    test_4x4.m[3][3]=4;

    float x = 4.0f/16.0f;
    float y = 8.0f/16.0f;
    float z = 12.0f/16.0f;
    Vec3d expected_result(x, y, z);

	
    std::cout << expected_result.toString() << std::endl;

    Vec3d before_vec(1.0f, 1.0f, 1.0f);
    Vec3d after_vec;

    Multiply_Matrix_Service::MultiplyMatrixVector(before_vec, after_vec, test_4x4);
    std::cout << "Vector Before Projection: " << before_vec.toString() << std::endl;
    std::cout << "Vector After Projection: " << after_vec.toString() << std::endl;
    
    if (after_vec==expected_result){
        std::cout << "Matrix Multiply got the correct answer" << std::endl;
    }else{
        std::cout << "Matrix Multiply got the wrong answer" << std::endl;
    }



    SDL_Quit();
    return 0; 
}
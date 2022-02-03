#include <SDL2/SDL.h>
#include "Triangle_Modifier.h"
#include "Multiply_Matrix_Service.h"


Rotator::Rotator(float x_degrees, float z_degrees, Vec3d center){
    x_degs = x_degrees;
    z_degs = z_degrees;
    center_of_rotation = center;

    //X Rotation MAtrix
    mat_XRot.m[0][0] = 1;
    mat_XRot.m[0][1] = 0;
    mat_XRot.m[0][2] = 0;
    mat_XRot.m[0][3] = 0;

    mat_XRot.m[1][0] = 0;
    mat_XRot.m[1][1] = SDL_cosf(x_degs*(3.14159265/180.0));
    mat_XRot.m[1][2] = SDL_sinf(x_degs*(3.14159265/180.0));
    mat_XRot.m[1][3] = 0;

    mat_XRot.m[2][0] = 0;
    mat_XRot.m[2][1] = -SDL_sinf(x_degs*(3.14159265/180.0));
    mat_XRot.m[2][2] = SDL_cosf(x_degs*(3.14159265/180.0));
    mat_XRot.m[2][3] = 0;

    mat_XRot.m[3][0] = 0;
    mat_XRot.m[3][0] = 0;
    mat_XRot.m[3][2] = 0;
    mat_XRot.m[3][3] = 1;

    //Z Rotation Matrix
    mat_ZRot.m[0][0] = SDL_cosf(z_degs*(3.14159265/180.0));
    mat_ZRot.m[0][1] = SDL_sinf(z_degs*(3.14159265/180.0));
    mat_XRot.m[0][2] = 0;
    mat_XRot.m[0][3] = 0;

    mat_ZRot.m[1][0] = -SDL_sinf(z_degs*(3.14159265/180.0));
    mat_ZRot.m[1][1] = SDL_cosf(z_degs*(3.14159265/180.0));
    mat_XRot.m[1][2] = 0;
    mat_XRot.m[1][3] = 0;

    mat_XRot.m[2][0] = 0;
    mat_XRot.m[2][1] = 0;
    mat_XRot.m[2][2] = 1;
    mat_XRot.m[2][3] = 0;

    mat_XRot.m[3][0] = 0;
    mat_XRot.m[3][0] = 0;
    mat_XRot.m[3][2] = 0;
    mat_XRot.m[3][3] = 1;
    		

}

void Rotator::ModifyTri(Triangle &tri){
    std::cout << "Rotating Triangle" << std::endl;
    std::cout << tri.toString() << std::endl;
    std::cout << "Done Rotating Triangle" << std::endl;
    Triangle triRotated;
    if (z_degs!=0){
        MultiplyMatrixVector(tri.getTrianglePoint(0), triRotated.getTrianglePoint(0), mat_ZRot);
        MultiplyMatrixVector(tri.getTrianglePoint(1), triRotated.getTrianglePoint(1), mat_ZRot);
        MultiplyMatrixVector(tri.getTrianglePoint(2), triRotated.getTrianglePoint(2), mat_ZRot);
    }
}

Translator::Translator(float x_distance, float z_distance){
    x_dist = x_distance;
    z_dist = z_distance;
}

void Translator::ModifyTri(Triangle &tri){
    std::cout << "Translating Triangle" << std::endl;
    std::cout << tri.toString() << std::endl;
    std::cout << "Done Translating Triangle" << std::endl;
}


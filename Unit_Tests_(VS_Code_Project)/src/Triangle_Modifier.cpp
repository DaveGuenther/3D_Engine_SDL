#include "Triangle_Modifier.h"


Rotator::Rotator(float x_degrees, float z_degrees, Vec3d center){
    x_degs = x_degrees;
    z_degs = z_degrees;
    center_of_rotation = center;
}

void Rotator::ModifyTri(Triangle &tri){
    std::cout << "Rotating Triangle" << std::endl;
    std::cout << tri.toString() << std::endl;
    std::cout << "Done Rotating Triangle" << std::endl;
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


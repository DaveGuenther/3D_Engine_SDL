#include <iostream>
#include <memory>
#include "../src/utility/Triangle.h"

int main(){
    Vec3d pt0{1.0f, 2.0f, 3.0f};
    Vec3d pt1{4.0f, 5.0f, 6.0f};
    Vec3d pt2{7.0f, 8.0f, 9.0f};
    Vec3d pt3{10.0f, 11.0f, 12.0f};
    Vec3d pt4{13.0f, 14.0f, 15.0f};
    Vec3d pt5{16.0f, 17.0f, 18.0f};
    

    std::cout << "Triangle Tester" << std::endl;
    Triangle first_tri{pt0, pt1, pt2, 0};
    Triangle second_tri{pt3, pt4, pt5, 1};
    Triangle& first_tri_ref=first_tri;
    std::unique_ptr<Triangle> my_tri_ptr = std::make_unique<Triangle>(first_tri);
    Triangle third_tri;
    third_tri=second_tri;


    return 0;
}
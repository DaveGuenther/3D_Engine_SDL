#include <iostream>
#include <vector>
#include "Vec2d.h"

 void print_vector(const std::vector<Vec2d> &this_vector){
     for (auto vec:this_vector){
        vec.print();
     }
 }

int main(){
    int x=1;
    int y=1;
    Vec2d my_vec(x, y);
    my_vec.print();

    Vec2d copy_vec(my_vec);
    copy_vec.print();

    Vec2d empty_vec;
    empty_vec.print();

    float u = 2.5f;
    float v = -1.3f;

    Vec2d float_vec(u,v);
    float_vec.print();

    std::vector<Vec2d> my_points = {my_vec, empty_vec,Vec2d(1,4)};
    print_vector(my_points);

    // Equality Test
    if (Vec2d(0,5)==Vec2d(0,5))
    {
        std::cout << "Vectors Matched!" << std::endl;
    }else{
        std::cout << "Vectors are Different" << std::endl;
    }

    //Inequality Test
    if (Vec2d(0,5)!=Vec2d(0,6))
    {
        std::cout << "Vectors are Different" << std::endl;
    }else{
        std::cout << "Vectors Matched!" << std::endl;
    }    

    return 0;
}
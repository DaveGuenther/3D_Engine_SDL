#include <iostream>
#include <vector>
#include "Vec2d.h"

 void print_vector(const std::vector<Vec2d> &this_vector){
     for (auto vec:this_vector){
        std::cout << vec.toString() << std::endl;
     }
 }

int main(){
    int x=1;
    int y=1;
    Vec2d my_vec(x, y);
    std::cout << my_vec.toString() << std::endl;

    Vec2d copy_vec(my_vec);
    std::cout << copy_vec.toString() << std::endl;

    Vec2d empty_vec;
    std::cout << empty_vec.toString() << std::endl;

    float u = 2.5f;
    float v = -1.3f;

    Vec2d float_vec(u,v);
    std::cout << float_vec.toString() << std::endl;

    std::vector<Vec2d> my_points = {my_vec, empty_vec,Vec2d(1,4)};
    print_vector(my_points);

    Vec2d incremental_vec;
    incremental_vec.setX(0);
    incremental_vec.setY(-5);
    std::cout << incremental_vec.toString() << std::endl;

    // testing getters
    if (incremental_vec.getX()==0 && incremental_vec.getY()==-5){
        std::cout << "Getters working" << std::endl;
    }else{
        std::cout << "Getter broken" << std::endl;
    }

        if (incremental_vec.getX()==-1 && incremental_vec.getY()==-5){
        std::cout << "Getters broken" << std::endl;
    }else{
        std::cout << "Getters working" << std::endl;
    }

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
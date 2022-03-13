#include <iostream>
#include <vector>
#include "Vec3d.h"

 void print_vector(const std::vector<Vec3d> &vectors){
     for (auto vec:vectors){
        std::cout << vec.toString() << std::endl;
     }
 }

int main(){
    int x=1;
    float y=1;
    float z=.5f;
    Vec3d my_vec(x, y, z);
    std::cout << my_vec.toString() << std::endl;

    Vec3d copy_vec(my_vec);
    std::cout << copy_vec.toString() << std::endl;

    Vec3d empty_vec;
    std::cout << empty_vec.toString() << std::endl;

    float u = 2.5f;
    float v = -1.3f;
    float w = -10.5f;

    Vec3d float_vec(u,v,w);
    std::cout << float_vec.toString() << std::endl;

    std::vector<Vec3d> my_points = {my_vec, empty_vec,Vec3d(1,4,5)};
    print_vector(my_points);


    Vec3d incremental_vec;
    incremental_vec.setX(0);
    incremental_vec.setY(-5);
    incremental_vec.setZ(-100.0f);
    std::cout << incremental_vec.toString() << std::endl;

    // testing getters
    if (incremental_vec.getX()==0 && incremental_vec.getY()==-5 && incremental_vec.getZ()==-100){
        std::cout << "Getters working" << std::endl;
    }else{
        std::cout << "Getter broken" << std::endl;
    }

        if (incremental_vec.getX()==-1 && incremental_vec.getY()==-5 && incremental_vec.getZ()==-100){
        std::cout << "Getters broken" << std::endl;
    }else{
        std::cout << "Getters working" << std::endl;
    }

    // Equality Test
    if (Vec3d(0,5,1)==Vec3d(0,5,1))
    {
        std::cout << "Vectors Matched!" << std::endl;
    }else{
        std::cout << "Vectors are Different" << std::endl;
    }

    //Inequality Test
    if (Vec3d(0,5,1)!=Vec3d(0,5,-1))
    {
        std::cout << "Vectors are Different" << std::endl;
    }else{
        std::cout << "Vectors Matched!" << std::endl;
    }    
    return 0;
}
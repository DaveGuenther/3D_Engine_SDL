// This script performs tests on the Triangle class
// Will test basic instantiation, setting, and getting
// will also test vectors of Triangles, passing and modification

#include <iostream>
#include <vector>
#include "Triangle.h"

int main(){
    Triangle my_triangle(Vec3d(0,0,0),Vec3d(1,1,1), Vec3d(2,2,2));
    Triangle my_triangle_2(Vec3d(-1,-1,-1),Vec3d(-2,-2,-2), Vec3d(-3,-3,-3));

    my_triangle.print();

    Triangle incremental_triangle;
    incremental_triangle.setTrianglePoint(0,Vec3d(0,0,10));
    incremental_triangle.setTrianglePoint(1,Vec3d(50,0,-50));
    incremental_triangle.setTrianglePoint(2,Vec3d(100,4,2));

    incremental_triangle.print();

    // testing getters
    if (incremental_triangle.getTrianglePoint(0)==Vec3d(0,0,10) &&
        incremental_triangle.getTrianglePoint(1)==Vec3d(50,0,-50) &&
        incremental_triangle.getTrianglePoint(2)==Vec3d(100,4,2)){
        std::cout << "Getters working" << std::endl;
    }else{
        std::cout << "Getter broken" << std::endl;
    }

        if (incremental_triangle.getTrianglePoint(0)==Vec3d(0,1,10) &&
        incremental_triangle.getTrianglePoint(1)==Vec3d(50,0,-50) &&
        incremental_triangle.getTrianglePoint(2)==Vec3d(100,4,2)){
        std::cout << "Getters broken" << std::endl;
    }else{
        std::cout << "Getters working" << std::endl;
    }    
   

    //std::vector<Triangle> tris;


return 0;
}
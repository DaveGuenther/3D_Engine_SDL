// This script performs tests on the Triangle class
// Will test basic instantiation, setting, and getting
// will also test vectors of Triangles, passing and modification

#include <iostream>
#include <vector>
#include "../include/Triangle.h"

int main(){
    Triangle my_triangle(Vec3d{0,0,0},Vec3d{1,1,1}, Vec3d{2,2,2});
    
    for (int i=0;i<3;i++){
        std::cout << my_triangle.p[i].x << my_triangle.p[i].y << my_triangle.p[i].z << std::endl;
    }

    //std::vector<Triangle> tris;


return 0;
}
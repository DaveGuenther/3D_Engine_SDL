// This script performs tests on the Triangle class
// Will test basic instantiation, setting, and getting
// will also test vectors of Triangles, passing and modification

#include <iostream>
#include <vector>
#include "Triangle.h"

 void print_vector(const std::vector<Triangle> &tris){
     for (auto tri:tris){
        std::cout << tri.toString() << std::endl;
     }
 }

int main(){
    Triangle my_triangle(Vec3d(0,0,0),Vec3d(1,1,1), Vec3d(2,2,2));
    Triangle my_triangle_2(Vec3d(-1,-1,-1),Vec3d(-2,-2,-2), Vec3d(-3,-3,-3));

    std::cout << my_triangle.toString() << std::endl;

    Triangle incremental_triangle;
    incremental_triangle.setTrianglePoint(0,Vec3d(0,0,10));
    incremental_triangle.setTrianglePoint(1,Vec3d(50,0,-50));
    incremental_triangle.setTrianglePoint(2,Vec3d(100,4,2));

    std::cout << incremental_triangle.toString() << std::endl;

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
   

    std::vector<Triangle> tris;
    for (int x=0;x<10;x++){
        tris.push_back(Triangle(Vec3d(-x,-x,-x),Vec3d(x,x,x), Vec3d(x+10,x+10,x+10)));
    }

    print_vector(tris);

    // add 1 to point1.x of each triangle and subtract 1 from point3.z of each tringle in the vector
    for (auto &tri : tris){
        
        Vec3d new_x_point = Vec3d(
            tri.getTrianglePoint(0).getX()+1,
            tri.getTrianglePoint(0).getY(),
            tri.getTrianglePoint(0).getZ());
        
        Vec3d new_z_point = Vec3d(
            tri.getTrianglePoint(2).getX(),
            tri.getTrianglePoint(2).getY(),
            tri.getTrianglePoint(2).getZ()-1);
        
        tri.setTrianglePoint(0,new_x_point);
        tri.setTrianglePoint(2,new_z_point);
    }

    std::cout << "Printing tris after all modifications" << std::endl;
    print_vector(tris);

return 0;
}
#include <iostream>
#include <memory>
#include <vector>
#include "../src/utility/Triangle.h"

int main(){
    Vec3d pt0{1.0f, 2.0f, 3.0f};
    Vec3d pt1{4.0f, 5.0f, 6.0f};
    Vec3d pt2{7.0f, 8.0f, 9.0f};

    

    std::cout << "Triangle Tester" << std::endl;
    Triangle first_tri{pt0, pt1, pt2, 0};
    Triangle& first_tri_ref=first_tri;

    Vec3d pt3{10.0f, 11.0f, 12.0f};
    Vec3d pt4{13.0f, 14.0f, 15.0f};
    Vec3d pt5{16.0f, 17.0f, 18.0f};    
    Triangle second_tri{pt3, pt4, pt5, 1};
    Triangle third_tri;
    third_tri=second_tri;
    
    std::vector<Triangle> my_vec;
    my_vec.push_back(second_tri);
   
    std::unique_ptr<Triangle> my_tri_ptr = std::make_unique<Triangle>(first_tri);
    
    std::cout << my_tri_ptr.get() << std::endl;

    std::unique_ptr<Triangle> new_tri_ptr;
    std::cout << new_tri_ptr.get() << std::endl;
    

    





    std::cout << "Breakpoint" << std::endl;
    std::cout << "Breakpoint2" << std::endl;
    
    /*
    // Simulate Triangle copy operations here...
    Vec3d _pt1 = *(second_tri.p[0]);
    Vec3d _pt2 = *(second_tri.p[1]);
    Vec3d _pt3 = *(second_tri.p[2]);

    third_tri.p[0]=std::make_unique<Vec3d>(_pt1);
    third_tri.p[1]=std::make_unique<Vec3d>(_pt2);
    third_tri.p[2]=std::make_unique<Vec3d>(_pt3);

    third_tri.tri_id = second_tri.tri_id;
    third_tri.color = second_tri.color;
    third_tri.textureCoords[0] = second_tri.textureCoords[0];
    third_tri.textureCoords[1] = second_tri.textureCoords[1];
    third_tri.textureCoords[2] = second_tri.textureCoords[2];
    third_tri.texture_ptr=second_tri.texture_ptr;  // Careful changing this to a unique_ptr!  It's used by MANY triangles
    third_tri.dim_amount=second_tri.dim_amount;
    */
    return 0;
}
#include <vector>
#include <SDL2/SDL.h>
#include "Mesh_Pipeline.h"
#include "Triangle_Modifier.h"
#include <string>
#include "Mat4x4.h"
#include <chrono>


Mat4x4* mat_XRot;

void local_modify_tri(Triangle &tri);

void local_modify_tri(Triangle &tri){
    Vec3d this_point = tri.getTrianglePoint(0);

    this_point.setX(this_point.getX()-1);
    this_point.setY(this_point.getY()-1);
    this_point.setZ(this_point.getZ()-1);
    tri.setTrianglePoint(0,this_point);
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    Mesh_Pipeline my_pipeline;
    my_pipeline.Add_Mesh_to_Pipeline("block.mesh");
    my_pipeline.Add_Mesh_to_Pipeline("pyramid.mesh");
    
    float x_deg=20;
    float y_deg=0;
    float z_deg=20;
    Vec3d center=Vec3d(0,0,0);
    int i;
    std::vector<Triangle_Modifier*> modifications;
    modifications.push_back(new Translator(10, 0, 0));
    for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
    modifications.push_back(new Rotator(x_deg, y_deg, z_deg, center));
    modifications.back()->AssignToMesh(1);
    modifications.push_back(new Translator(0, 5, 0));
    for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
    modifications.push_back(new Rotator(x_deg, y_deg, z_deg, center));
    for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}
    modifications.push_back(new Translator(0, 0, 5));
    for(i=0;i<my_pipeline.GetSize();i++){ modifications.back()->AssignToMesh(i);}

    //Triangle my_triangle(Vec3d(0.5f,0.6f,0.7f),Vec3d(1.1f,1.2f,1.3f), Vec3d(2.4f,2.5f,2.6f), 3);
    //std::cout << my_triangle.toString() << std::endl;
    my_pipeline.Apply_Modifications(modifications);

    /*std::vector<Triangle> tris = myMesh.get_tris();
    for (auto triMod:modifications){
        for (auto &tri:tris){
            std::cout << "Preparing to modify: " << tri.toString() << std::endl;
            triMod->ModifyTri(tri);
            
        }
    }*/

/*


	//Triangle_Modifier my_tri = new Rotator(x_deg, z_deg, center);
    //std::vector<IFunnyInterface*> ifVec;
    Triangle my_triangle(Vec3d(0.5f,0.6f,0.7f),Vec3d(1.1f,1.2f,1.3f), Vec3d(2.4f,2.5f,2.6f));
    std::cout << "Local modifications to triangle by reference" << std::endl;
    std::cout << my_triangle.toString() << std::endl;

    local_modify_tri(my_triangle);
    std::cout << my_triangle.toString() << std::endl;


    std::cout << "ModifyTri modifications to triangle by reference" << std::endl;
    //Triangle my_triangle(Vec3d(0,0,0),Vec3d(1,1,1), Vec3d(2,2,2));
    std::cout << my_triangle.toString() << std::endl;

    for (auto triMod:modifications){
        triMod->ModifyTri(my_triangle);
        
    }
    std::cout << my_triangle.toString() << std::endl;
    
*/
  
    SDL_Quit();
    return 0;
}
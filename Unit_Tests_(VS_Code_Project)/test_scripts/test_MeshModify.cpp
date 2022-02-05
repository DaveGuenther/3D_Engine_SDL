#include <vector>
#include <SDL2/SDL.h>
#include "Mesh.h"
#include <string>
#include "Triangle.h"
#include "Mat4x4.h"
#include <chrono>

Mat4x4* mat_XRot;
 

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    Mesh myMesh;
    myMesh.Load_Mesh("block.mesh");

/*
    std::vector<Triangle> tris = myMesh.get_tris();
    for (auto tri:tris){
        std::cout << tri.toString() << std::endl;
    }
*/


    float x_deg=5;
    float z_deg=45;
    Vec3d center=Vec3d(0,0,0);
	//Triangle_Modifier my_tri = new Rotator(x_deg, z_deg, center);
    //std::vector<IFunnyInterface*> ifVec;

    std::vector<Triangle_Modifier*> modifications;
    modifications.push_back(new Rotator(x_deg, z_deg, center));
    modifications.push_back(new Translator(10,5));

    Triangle my_triangle(Vec3d(0,0,0),Vec3d(1,1,1), Vec3d(2,2,2));
    std::cout << my_triangle.toString() << std::endl;

    for (auto triMod:modifications){
        triMod->ModifyTri(my_triangle);
        
    }
    std::cout << my_triangle.toString() << std::endl;
    

  
    SDL_Quit();
    return 0;
}
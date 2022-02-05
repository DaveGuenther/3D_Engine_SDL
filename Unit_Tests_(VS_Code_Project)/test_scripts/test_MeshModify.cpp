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


    std::vector<Triangle> tris = myMesh.get_tris();
    for (auto tri:tris){
        std::cout << tri.toString() << std::endl;
    }

    Triangle my_triangle(Vec3d(0,0,0),Vec3d(1,1,1), Vec3d(2,2,2));

    float x_deg=5;
    float z_deg=45;
    Vec3d center=Vec3d(0,0,0);
	//Triangle_Modifier my_tri = new Rotator(x_deg, z_deg, center);
    //std::vector<IFunnyInterface*> ifVec;

    std::vector<Triangle_Modifier*> tri_vec;
    tri_vec.push_back(new Rotator(x_deg, z_deg, center));
    tri_vec.push_back(new Translator(10,5));

    for (auto tri:tri_vec){
        tri->ModifyTri(my_triangle);
        
    }

  
    SDL_Quit();
    return 0;
}
#include <vector>
#include <SDL2/SDL.h>
#include "Mesh.h"
#include <string>
#include "Triangle.h"
#include "Mat4x4.h"
#include "trig_function.h"
#include <chrono>

Mat4x4* mat_XRot;
Deg_Sin mySin;
Deg_Cos myCos; 

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    Mesh myMesh;
    myMesh.Load_Mesh("block.mesh");

    auto start = std::chrono::high_resolution_clock::now();
    for (int i=-1000;i<1000;i++){ mySin.get(i);}
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "2k sin values on Lookup (microseconds): " << duration.count() << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i=-1000;i<1000;i++){ SDL_sinf(i*(3.1415926535f/180));}
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
    std::cout << "2k sin values on SDL calculated (microseconds): " << duration2.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i=-1000;i<1000;i++){ myCos.get(i);}
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "2k cos values on Lookup (microseconds): " << duration.count() << std::endl;

    start2 = std::chrono::high_resolution_clock::now();
    for (int i=-1000;i<1000;i++){ SDL_cosf(i*(3.1415926535f/180));}
    stop2 = std::chrono::high_resolution_clock::now();
    duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
    std::cout << "2k cos values on SDL calculated (microseconds): " << duration2.count() << std::endl;

    std::cout << mySin.get(0) << mySin.get(45) << mySin.get(90) << std::endl;


		// X Rotation Matrix
    //mat_XRot->m[0][0] = 1;
    //mat_XRot->m[1][1] = SDL_cosf(tTheta/2*(3.14159265/180.0));
    //mat_XRot->m[1][2] = SDL_sinf(tTheta/2*(3.14159265/180.0));
    //mat_XRot->m[2][1] = -SDL_sinf(tTheta/2*(3.14159265/180.0));
    //mat_XRot->m[2][2] = SDL_cosf(tTheta/2*(3.14159265/180.0));
    //mat_XRot->m[3][3] = 1;	

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
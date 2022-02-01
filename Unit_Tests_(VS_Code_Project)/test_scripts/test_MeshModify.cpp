#include <vector>
#include "Mesh.h"

int main(){
    Mesh myMesh;
    myMesh.Load_Mesh("block.mesh");

    std::vector<Triangle> tris = myMesh.get_tris();
    for (auto tri:tris){
        std::cout << tri.toString() << std::endl;
    }
    return 0;
}
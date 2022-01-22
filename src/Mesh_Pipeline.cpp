#include "Mesh_Pipeline.h"
#include "Mesh.h"
#include <string>


Mesh_Pipeline::Mesh_Pipeline(){

}

void Mesh_Pipeline::Add_Mesh_to_Pipeline(Mesh this_mesh){
    Meshes.push_back(this_mesh);
}

void Mesh_Pipeline::Add_Mesh_to_Pipeline(std::string filename){
    Meshes.push_back(Mesh());
    Meshes.back().Load_Mesh(filename); 
}

std::vector<Mesh> Mesh_Pipeline::Get_Meshes(){
    return Meshes;
}
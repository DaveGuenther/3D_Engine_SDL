#include <string>
#include "Mesh_Pipeline.h"
#include "Mesh.h"



Mesh_Pipeline::Mesh_Pipeline(){

}

std::vector<Mesh>& Mesh_Pipeline::Get_Meshes(){
    return Meshes;
}

void Mesh_Pipeline::Add_Mesh_to_Pipeline(std::string filename){
    Meshes.push_back(Mesh());
    Meshes.back().Load_Mesh(filename); 
}

void Mesh_Pipeline::Add_Mesh_to_Pipeline(Mesh this_mesh){
    Meshes.push_back(this_mesh);
}

void Mesh_Pipeline::Set_Rot_Angle_Changes_for_Pipeline(float fTheta_in, float tTheta_in){
    for (auto this_mesh: Meshes){
        
        this_mesh.Set_Rot_Angles(this_mesh.get_fTheta()+fTheta_in, this_mesh.get_tTheta()+tTheta_in);
    }
}
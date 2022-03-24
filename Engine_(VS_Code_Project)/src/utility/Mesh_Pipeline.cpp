#include <string>

#include "utility/Mesh.h"
#include "utility/Mesh_Pipeline.h"




Mesh_Pipeline::Mesh_Pipeline(){
    total_mesh_ids=0;
}

std::vector<Mesh>& Mesh_Pipeline::Get_Meshes(){
    return Meshes;
}

void Mesh_Pipeline::Add_Mesh_to_Pipeline(std::string filename, Vec3d origin){
    Mesh new_mesh(total_mesh_ids);
    new_mesh.loadMesh(filename);
    Meshes.push_back(new_mesh);
    
    int this_mesh_id = new_mesh.getID();
    Triangle_Modifier* this_mod = new Translator(origin.getX(), origin.getY(), origin.getZ());
    this_mod->assignToMesh(this_mesh_id);
    std::vector<Triangle_Modifier *> tri_mods_pipe;
    tri_mods_pipe.push_back(this_mod);
    this->Apply_Modifications(tri_mods_pipe);
    

    total_mesh_ids+=1;
}

void Mesh_Pipeline::Add_Mesh_to_Pipeline(Mesh this_mesh){
    this_mesh.setID(total_mesh_ids);
    Meshes.push_back(this_mesh);
    total_mesh_ids+=1;
}

void Mesh_Pipeline::Apply_Modifications(std::vector<Triangle_Modifier*> tri_mods_pipe){

    for (auto triMod:tri_mods_pipe){
        std::vector<int> mesh_ids = triMod->getAssignedMeshIDs();
        for (int this_mesh_id:mesh_ids){
            //std::cout << "Preparing to modify: " << Meshes[this_mesh_id].toString() << std::endl;
            Meshes[this_mesh_id].performModifications(triMod);
            
        }
    }
}

int Mesh_Pipeline::GetSize(){
    return total_mesh_ids;
}
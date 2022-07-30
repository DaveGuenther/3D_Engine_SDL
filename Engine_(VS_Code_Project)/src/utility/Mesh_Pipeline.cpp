#include <string>
#include <memory>

#include "utility/Mesh.h"
#include "utility/Mesh_Pipeline.h"
#include "materials/TextureList.h"
#include "objects/OBJ.h"





Mesh_Pipeline::Mesh_Pipeline(std::shared_ptr<TextureList> texture_list){
    total_mesh_ids=0;
    this->texture_list=texture_list;
}

Mesh_Pipeline::~Mesh_Pipeline(){
   

}


std::vector<Mesh>& Mesh_Pipeline::Get_Meshes(){
    return Meshes;
}

void Mesh_Pipeline::Add_Mesh_to_Pipeline(std::string filename, Vec3d origin){
    Mesh new_mesh(total_mesh_ids);
    new_mesh.loadMesh(filename);
    Meshes.push_back(new_mesh);
    
    int this_mesh_id = new_mesh.getID();
    std::shared_ptr<Triangle_Modifier> this_mod(new Translator(origin.getX(), origin.getY(), origin.getZ()));
    this_mod->assignToMesh(this_mesh_id);
    std::vector<std::shared_ptr<Triangle_Modifier>> tri_mods_pipe;
    tri_mods_pipe.push_back(this_mod);
    this->Apply_Modifications(tri_mods_pipe);    

    total_mesh_ids+=1;
}

void Mesh_Pipeline::Add_OBJ_Mesh_to_Pipeline(std::string filename, Vec3d origin, Vec3d rotation){
    OBJ thisOBJ(filename, texture_list);
    std::vector<Mesh> OBJ_meshes;
    OBJ_meshes = thisOBJ.getMeshes();

    for (auto new_mesh:OBJ_meshes){
        new_mesh.setID(total_mesh_ids);
        Meshes.push_back(new_mesh);
        int this_mesh_id = new_mesh.getID();
        
        std::shared_ptr<Triangle_Modifier> this_rotate_mod(new Rotator(rotation.getX(), rotation.getY(), rotation.getZ(), Vec3d(0,0,0)));
        std::shared_ptr<Triangle_Modifier> this_translate_mod(new Translator(origin.getX(), origin.getY(), origin.getZ()));
        this_rotate_mod->assignToMesh(this_mesh_id);
        this_translate_mod->assignToMesh(this_mesh_id);

        std::vector<std::shared_ptr<Triangle_Modifier>> tri_mods_pipe;
        tri_mods_pipe.push_back(this_rotate_mod);
        tri_mods_pipe.push_back(this_translate_mod);

        this->Apply_Modifications(tri_mods_pipe);    
            
        total_mesh_ids+=1;    
    }
    
    
    
}

void Mesh_Pipeline::Add_Mesh_to_Pipeline(Mesh this_mesh){
    this_mesh.setID(total_mesh_ids);
    Meshes.push_back(this_mesh);
    total_mesh_ids+=1;
}

void Mesh_Pipeline::Apply_Modifications(std::vector<std::shared_ptr<Triangle_Modifier>> tri_mods_pipe){

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
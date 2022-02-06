#include <string>
#include "Mesh_Pipeline.h"
#include "Mesh.h"



Mesh_Pipeline::Mesh_Pipeline(){
    total_mesh_ids=0;
}

std::vector<Mesh>& Mesh_Pipeline::Get_Meshes(){
    return Meshes;
}

void Mesh_Pipeline::Add_Mesh_to_Pipeline(std::string filename){
    Mesh new_mesh;
    new_mesh.Load_Mesh(filename);
    new_mesh.set_ID(total_mesh_ids);
    Meshes.push_back(new_mesh);
    /*
    Meshes.push_back(Mesh());
    Meshes.back().Load_Mesh(filename); 
    Meshes.back().set_ID(total_mesh_ids);*/
    total_mesh_ids+=1;
}

void Mesh_Pipeline::Add_Mesh_to_Pipeline(Mesh this_mesh){
    this_mesh.set_ID(total_mesh_ids);
    Meshes.push_back(this_mesh);
    total_mesh_ids+=1;
}

void Mesh_Pipeline::Set_Rot_Angle_Changes_for_Pipeline(float fTheta_in, float tTheta_in){
    for (auto this_mesh: Meshes){
        
        this_mesh.Set_Rot_Angles(this_mesh.get_fTheta()+fTheta_in, this_mesh.get_tTheta()+tTheta_in);
    }
}

void Mesh_Pipeline::Apply_Modifications(std::vector<Triangle_Modifier*> tri_mods_pipe){
    /*auto &tri_mods = tri_mods_pipe.getModifications();
    for (auto mesh:Meshes){
        mesh.PerformModifications(tri_mods);
    }*/
    for (auto triMod:tri_mods_pipe){
        std::vector<int> mesh_ids = triMod->GetAssignedMeshIDs();
        for (int this_mesh_id:mesh_ids){
            std::cout << "Preparing to modify: " << Meshes[this_mesh_id].toString() << std::endl;
            Meshes[this_mesh_id].PerformModifications(triMod);
            
        }
        
        /*for (auto &tri:tris){
            std::cout << "Preparing to modify: " << tri.toString() << std::endl;
            triMod->ModifyTri(tri);
            
        }*/
    }
}

int Mesh_Pipeline::GetSize(){
    return total_mesh_ids;
}
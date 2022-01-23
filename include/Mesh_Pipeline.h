#ifndef MESH_PIPELINE_H
#define MESH_PIPELINE_H

#include <vector>
#include "Mesh.h"

/**
 * @brief The Mesh_Pipeline class will hold a vector of Mesh objects.  It's instances will be passes to the Translator, Rotator, and Renderer classes
 * 
 */
class Mesh_Pipeline{
    private:

    std::vector<Mesh> Meshes;

    public:
    Mesh_Pipeline();

    /**
     * @brief This function loads data from a file into a Mesh object and adds it to the mesh pipeline
     * 
     * @param filename this is a file name of the mesh such as "block.mesh"
     */
    void Add_Mesh_to_Pipeline(std::string filename);

    /**
     * @brief this function adds a Mesh to the Meshes pipeline
     * 
     * @param this_mesh this is an instance of the Mesh class
     */
    void Add_Mesh_to_Pipeline(Mesh this_mesh);



    /**
     * @brief 
     * 
     * @return std::vector<Mesh> 
     */
    std::vector<Mesh> Get_Meshes();

    void Set_Rot_Angle_Changes_for_Pipeline(float fTheta_in, float tTheta_in);

};

#endif
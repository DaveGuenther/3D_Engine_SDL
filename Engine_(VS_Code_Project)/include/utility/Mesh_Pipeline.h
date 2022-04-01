#ifndef MESH_PIPELINE_H
#define MESH_PIPELINE_H

#include <vector>
#include "Mesh.h"


/**
 * @brief The Mesh_Pipeline class will hold a vector of Mesh objects.  It is responsible for loading and managing meshes.  It is also responsible for applying mesh modifications
 * 
 */
class Mesh_Pipeline{
    private:

    /**
     * @brief The Meshes vector of the Mesh_Pipeline class is the key data object of the class.
     * 
     */
    std::vector<Mesh> Meshes;

    /**
     * @brief this integer is always set to the maximum number of meshes in the pipeline.  Every time a mesh is added, this number is incremented.
     * 
     */
    int total_mesh_ids;

    public:
    Mesh_Pipeline();
    ~Mesh_Pipeline();
    /**
     * @brief This function loads data from a file into a Mesh object and adds it to the mesh pipeline
     * 
     * @param filename this is a file name of the mesh such as "block.mesh"
     * @param origin this is a Vec3d that represents the x, y, and z location to initially place the mesh in 3D space
     */
    void Add_Mesh_to_Pipeline(std::string filename, Vec3d origin);

    /**
     * @brief this function adds a Mesh to the Meshes vector (the pipeline)
     * 
     * @param this_mesh this is an instance of the Mesh class
     */
    void Add_Mesh_to_Pipeline(Mesh this_mesh);

    /**
     * @brief This function applies a vector of Triangle_Modifiers (Rotations or Translations) to the meshes that each of them target.  
     * 
     * @param tri_mods_pipe Each Triangle_Modifier in this vector can apply to one or more Meshes as determined by that modifier.
     */
    void Apply_Modifications(std::vector<Triangle_Modifier*> tri_mods_pipe);
    
    /**
     * @brief Get the total number of meshes in the mesh pipeline
     * 
     * @return int 
     */
    int GetSize();

    /**
     * @brief Get the vector of Meshes for use when rendering the mesh pipeline
     * 
     * @return std::vector<Mesh>& 
     */
    std::vector<Mesh>& Get_Meshes();
};

#endif
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

    /**
     * @brief The Meshes vector of the Mesh_Pipeline class is really the ky data object itself.
     * 
     */
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
     * @brief this function adds a Mesh to the Meshes vector (the pipeline)
     * 
     * @param this_mesh this is an instance of the Mesh class
     */
    void Add_Mesh_to_Pipeline(Mesh this_mesh);



    /**
     * @brief This getter method is intended for mutability downstream by returning a reference to the mesh vector rather than the vector itself.  This way when the returned value is used in a for (auto& element: collection) expression, when each element is changed, those changes will be reflected back to the Meshes vector in this class.
     * 
     * @return std::vector<Mesh>& 
     */
    std::vector<Mesh>& Get_Meshes();

    /**
     * @brief Calling this method will add the fTheta and tTheta values to the fTheta and tTheta values of EVERY Mesh in the Mesh vector.  It is used to apply a rotation to the whole pipeline.
     * 
     * @param fTheta_in X Rotation angle (degrees)
     * @param tTheta_in Z Rotation angle (degrees)
     */
    void Set_Rot_Angle_Changes_for_Pipeline(float fTheta_in, float tTheta_in);

};

#endif
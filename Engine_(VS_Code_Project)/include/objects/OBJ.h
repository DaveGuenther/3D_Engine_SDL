#ifndef OBJ_H
#define OBJ_H

#include <string>
#include <fstream>
#include <sstream>

#include "utility/Mesh.h"

class OBJ_Datum{
    public:
    OBJ_Datum(std::string raw_mesh_data):meshblocks(new std::stringstream(raw_mesh_data)){ }
    std::stringstream* meshblocks;
    std::vector<std::string> this_mesh_block; // this is used to feed each line in succession to the stringstream so that it can be read using getline
    std::string mesh_name; // each mesh gets a name
    std::string mtl; // 
};


/**
 * @brief This class is the main object class used by the engine to load Blender OBJ files.  This class specifically works with the OBJ_Parse class to load and expose raw OBJ 
 * data, then this class assembles the mesh object from that data and provides it to the engine. 
 * 
 * Note on Blender usage to build .obj files.  When exporting a mesh in blender to .OBJ, use the following settings:
 * 
 */
class OBJ{
    private:

        /*struct OBJ_Datum{
            //std::stringstream& meshblocks;  // each stringstream will be a meshblock from the file delimited by lines that start with "o"
            std::string mesh_name; // each mesh gets a name
            std::string mtl; // 
        };*/

        std::vector<Mesh> Meshes;
        //std::vector<OBJ_Datum> OBJ_Data; 
        std::vector<OBJ_Datum> myOBJ_Data;
        bool peekline( std::ifstream & is, std::string & s );
        std::ifstream myfile;

        
    public:
        /**
         * @brief Construct a new OBJ object.  This passes the file name to the OBJ_Parse class.  Then it assembles the Mesh object from the raw vertex, normal, texture, and face
         * information from the OBJ_Parse class
         * 
         * @param filename std::string file name of the .obj file to be loaded.  In the future this class will handle materials and will pull that information from a .mtl file with 
         * the same name as the obj file
         */
        OBJ(std::string filename);

        /**
         * @brief Get the Mesh object.  This is the final mesh object loaded into the mesh pipeline
         * 
         * @return Mesh& 
         */
        std::vector<Mesh>& getMeshes();

        void split_OBJ_Chunks();

};

#endif
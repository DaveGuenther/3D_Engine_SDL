#ifndef OBJ_H
#define OBJ_H

#include <string>
#include <fstream>
#include <sstream>
#include <memory> // for smare ptrs

#include "utility/Mesh.h"
#include "materials/TextureList.h"
#include "materials/MTL.h"

/**
 * @brief This class is used to hold information about each mech chunk that is pulled from an fstream (including the stringstream itself)
 * 
 */
class OBJ_Datum{
    public:
    OBJ_Datum(std::string raw_mesh_data):meshblocks(new std::stringstream(raw_mesh_data)){ }
    std::shared_ptr<std::stringstream> meshblocks;
    std::vector<std::string> this_mesh_block; // this is used to feed each line in succession to the stringstream so that it can be read using getline
    std::string mesh_name; // each mesh gets a name
    std::vector<std::string> material; // each mesh can have multiple materials
};


/**
 * @brief This class is the main object class used by the engine to load Blender OBJ files.  This class specifically works with the OBJ_Parse class to load and expose raw OBJ 
 * data, then this class assembles the mesh object from that data and provides it to the engine. 
 * 
 * Note on Blender usage to build .obj files.  When exporting a mesh in blender to .OBJ, use the following settings:
 * 
 * Include:
 * - Objects as: OBJ Objects (CHECKED)
 * - Objects as: OBJ Groups (unchecked)
 * - Objects as: Material Groups (unchecked)
 * - Animation (unchecked)
 * 
 * Transform:
 * - Path Mode: Auto
 * - Forward: Z Forward
 * - Up: Y Up
 * 
 * Geometry (CHECK only the following settings, uncheck all others):
 * - Write Normals
 * - Include UVs
 * - Write Materials
 * - Triangulate Faces
 */
class OBJ{
 
    public:
        /**
         * @brief Default Constructor for a new OBJ object.  Use this when opening .OBJ files exported from Blender with Z Forward and Y Up.  Those files at still exported using CCW winding (Righthand Rule).
         * The default consutructor will accept the CCW windings and produce a mesh that is CW wound (left hand winding).  At the end, the engine needs to have triangles formatted using lefthand coordinates.
         * information from the OBJ_Parse class
         * 
         * @param filename std::string file name of the .obj file to be loaded.  In the future this class will handle materials and will pull that information from a .mtl file with 
         * the same name as the obj file
         */
        OBJ(std::string filename, std::shared_ptr<TextureList> texture_list);

        /**
         * @brief Construct a new OBJ object.  This is line the default constructor, except that it's intended for OBJ files where the faces are already defined in CW winding order rather than CCW.
         * 
         * @param filename 
         * @param forceClockwiseWinding This value will most likely be false if you are using this constructor and not the default
         * @param flip_X_Coords This value will most likely be false if you are using this constructor and now the default constructor
         */
        OBJ(std::string filename, bool forceClockwiseWinding, bool flip_X_Coords);

        /**
         * @brief Get the Mesh object.  This is the final mesh object loaded into the mesh pipeline
         * 
         * @return std::vector<Mesh>&  This class parses OBJ files which may contain multiple definitions of "objects" within the file (lines
         * that start with "o").  In order to properly pass this information back to the engine it means that a single OBJ file can end up producing 
         * multiple "Mesh" objects.  For this reason, we'll return a vector of meshes instead of a single mesh, even if it is a vector of one mesh. 
         */
        std::vector<Mesh>& getMeshes();



    private:
        /**
         * @brief This method will use an fstream to start parsing through the OBJ file.  it's going to be broken down into sections delimited with lines
         * that start with "o" to identify the start and stop of new object mesh definitions in the OBJ file.  This method will look through the fstream and 
         * create a stringstream of the data occuring between each "o" line.  This data along with the object name and material information will be stored in 
         * a vector of OBJ_Datum class instances (we'll call each instance a "chunk").
         * 
         */
        void split_OBJ_Chunks();
        
        /**
         * @brief This private function is used internally to the split_OBJ_Chunks() method.  It offers the ability to "peek ahead" in an std:ifstream and return
         * the nect token in a stream and then replace the cursor back at it's original place in the stream.  We use this to look ahead for object ("o") tokens or
         * end of file scenarios
         * 
         * @param is This is a reference to the ifstream
         * @param s this is the next token captured in the ifstream
         * @return true if there are still more tokens in the file
         * @return false if the next token results in an EOY scenario
         */
        bool peekline( std::ifstream & is, std::string & s );

        /**
         * @brief This goes through the object chunks located in the file (as stringstreams) and iterates over the vector creating OBJ_Chunk instances for ecah stringsttream.
         * The OBJ_Chunk class will handle further parsing of the individual lines in the chunk.
         * 
         */
        void assembleChunks();

        /**
         * @brief Called from the constructor, this method just opens the file and then calls split_OBJ_Chunks() and assembleChunks() respectively.
         * 
         * @param filename std::string filename of the OBJ file to load
         */
        void buildMesh(std::string filename);

        std::vector<Mesh> Meshes;
        std::vector<OBJ_Datum> myOBJ_Data;
        std::shared_ptr<TextureList> texture_list;
        std::shared_ptr<MTL> MTLfile;
        std::ifstream myfile;
        std::string filename;
        int totalVertices;
        int totalTextureCoords;
        bool forceClockwiseWinding;
        bool flip_X_Coords;

};

#endif
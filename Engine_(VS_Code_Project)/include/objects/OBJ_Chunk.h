#ifndef OBJ_CHUNK_H
#define OBJ_CHUNK_H

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "objects/OBJ_Lex_normal.h"
#include "objects/OBJ_Lex_textureCoord.h"
#include "objects/OBJ_Lex_triFace.h"
#include "objects/OBJ_Lex_vertex.h"

/**
 * @brief This class will examine a single stringstream consistin of the lines of an fstream file that define a single mesh
 * object and parse that object out into it's respective vertices, normals, texture coordinates, and triangle faces.
 * The class can return each of the parsed data elements for the calling class to assemble a mesh.
 * 
 */
class OBJ_Chunk{
    public:
        /**
         * @brief Construct a new obj chunk object.  This takes a stringstream representing the lines in an OBJ file that define a single object ("o").
         * 
         * 
         * @param this_mesh_object stringstream to the mesh object.
         */
        OBJ_Chunk(std::stringstream& this_mesh_object);
        /**
         * @brief Get the Total Vertex Num object.  This is used to ensure that we don't lose track of the vertex IDs that have already been captured 
         * in an OBJ file.
         * 
         * @return const int& 
         */
        const int& getTotalVertexNum();
        
        /**
         * @brief Get the Total Text Coord Num object.  This is the same as getTotalVertexNum, but it's trasking against the surface normals, not the vertices.
         * 
         * 
         * @return const int& 
         */
        const int& getTotalTextCoordNum();      
            
        std::vector<OBJ_Lex_vertex> vertices;
        std::vector<OBJ_Lex_textureCoord> textureCoords;
        std::vector<OBJ_Lex_normal> normals;
        std::vector<OBJ_Lex_triFace> triangleFaces;
      
    private:

        int totalVertices;
        int totalTextureCoords;


};

#endif
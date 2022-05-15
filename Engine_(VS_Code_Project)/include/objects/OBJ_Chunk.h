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

class OBJ_Chunk{
    public:
        OBJ_Chunk(std::stringstream& this_mesh_object);
        
        std::vector<OBJ_Lex_vertex> vertices;
        std::vector<OBJ_Lex_textureCoord> textureCoords;
        std::vector<OBJ_Lex_normal> normals;
        std::vector<OBJ_Lex_triFace> triangleFaces;
        const int& getTotalVertexNum();
        const int& getTotalTextCoordNum();        
    private:

        int totalVertices;
        int totalTextureCoords;


};

#endif
#ifndef OBJ_PARSE_H
#define OBJ_PARSE_H

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "objects/OBJ_normal.h"
#include "objects/OBJ_textureCoord.h"
#include "objects/OBJ_triFace.h"
#include "objects/OBJ_vertex.h"

class OBJ_Parse{
    public:
        OBJ_Parse(std::string filename);
        std::vector<OBJ_vertex>& getVertices();
        std::vector<OBJ_textureCoord>& getTextureCoords();
        std::vector<OBJ_normal>& getNormals();
        std::vector<OBJ_triFace>& getTriangleFaces();
        
        std::vector<OBJ_vertex> vertices;
        std::vector<OBJ_textureCoord> textureCoords;
        std::vector<OBJ_normal> normals;
        std::vector<OBJ_triFace> triangleFaces;
        
    private:

};

#endif
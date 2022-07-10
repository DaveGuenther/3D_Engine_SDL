#include <fstream>
#include <filesystem>
#include <sstream>
#include <iostream>

#include "SDL.h"
#include "objects/OBJ_Chunk.h"
#include "materials/MTL.h"


OBJ_Chunk::OBJ_Chunk(std::stringstream& this_mesh_object, const std::unordered_map<std::string, std::string>& mesh_MTLs){

    this->totalTextureCoords=0;
    this->totalVertices=0;
    std::string line,material_name, this_texture;
    std::string comment = "#";
    char linefeed = '\n';
    int tri_id=0;
    SDL_Color color; color.r=255; color.g=255; color.b=255; color.a=255; 
    while (std::getline(this_mesh_object, line)) {
        std::stringstream this_stream(line);
        std::string keyword, lexLine;
        std::getline(this_stream,keyword,' ');
        std::getline(this_stream,lexLine);
        
        if (keyword=="v"){ // Vertex
            OBJ_Lex_vertex this_vertex;
            this_vertex.lex(lexLine);
            this->vertices.push_back(this_vertex);
            totalVertices+=1;

        }else if (keyword=="vt"){ // texture coordinate
            OBJ_Lex_textureCoord this_textCoord;
            this_textCoord.lex(lexLine);
            this->textureCoords.push_back(this_textCoord);
            totalTextureCoords+=1;

        }else if (keyword=="vn"){ // normal vector
            OBJ_Lex_normal this_normal_vector;
            this_normal_vector.lex(lexLine);
            this->normals.push_back(this_normal_vector);

        }else if (keyword=="usemtl"){ // use material for each subsequent face until another usemtl is located
          
            material_name=lexLine;
            auto it = mesh_MTLs.find(material_name);
            if (it==mesh_MTLs.end()){
                this_texture = "not_found.png";
            }else{
                //Assign the texture file for the next set of faces
                this_texture = it->second;
            }

        }else if (keyword=="f"){ // triangle face
            OBJ_Lex_triFace this_triangle_face;
            this_triangle_face.lex(lexLine);
            this_triangle_face.texturefile = this_texture;
            this->triangleFaces.push_back(this_triangle_face);

        }else if (keyword=="mtllib"){ // material definition
            //std::cout << keyword << " material definition" << std::endl;


        }else if (keyword=="s"){ // use material
            
            std::cout << keyword << " s has been encountered..  get ready!" << std::endl;             

        }else{ // Comment or unsupported line..  Do nothing
            //std::cout << "Not Parsed" << std::endl;
        }
        

        
    }


}

const int& OBJ_Chunk::getTotalTextCoordNum(){ return totalTextureCoords; }

const int& OBJ_Chunk::getTotalVertexNum(){ return totalVertices; }
#include "objects/OBJ_Parse.h"

#include <SDL2/SDL.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <iostream>


OBJ_Parse::OBJ_Parse(std::stringstream& this_mesh_object){

    std::string line;
    std::string comment = "//";
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

        }else if (keyword=="vt"){ // texture coordinate
            OBJ_Lex_textureCoord this_textCoord;
            this_textCoord.lex(lexLine);
            this->textureCoords.push_back(this_textCoord);

        }else if (keyword=="vn"){ // normal vector
            OBJ_Lex_normal this_normal_vector;
            this_normal_vector.lex(lexLine);
            this->normals.push_back(this_normal_vector);

        }else if (keyword=="f"){ // triangle face
            OBJ_Lex_triFace this_triangle_face;
            this_triangle_face.lex(lexLine);
            this->triangleFaces.push_back(this_triangle_face);

        }else if (keyword=="mtllib"){ // material definition
            //std::cout << keyword << " material definition" << std::endl;

        }else if (keyword=="usemtl"){ // use material
            //std::cout << keyword << " use material" << std::endl;             

        }else if (keyword=="s"){ // use material
            
            std::cout << keyword << " s has been encountered..  get ready!" << std::endl;             

        }else{ // Comment or unsupported line..  Do nothing
            //std::cout << "Not Parsed" << std::endl;
        }
        

        
    }


}
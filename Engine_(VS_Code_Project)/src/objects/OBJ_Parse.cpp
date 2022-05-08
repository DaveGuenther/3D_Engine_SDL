#include "objects/OBJ_Parse.h"

#include <SDL2/SDL.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <iostream>


OBJ_Parse::OBJ_Parse(std::string filename){
    std::ifstream myfile;
	filename = "Meshes/"+filename;
	std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
	myfile.open (filename);

	if (myfile.is_open()) {
        std::string line;
        std::string comment = "//";
        char linefeed = '\n';
        int tri_id=0;
        SDL_Color color; color.r=255; color.g=255; color.b=255; color.a=255; 
        while (std::getline(myfile, line)) {
            std::stringstream this_stream(line);
            std::string keyword, lexLine;
            std::getline(this_stream,keyword,' ');
            std::getline(this_stream,lexLine);
            
            if (keyword=="v"){ // Vertex
                OBJ_vertex this_vertex;
                this_vertex.lex(lexLine);
                this->vertices.push_back(this_vertex);

            }else if (keyword=="vt"){ // texture coordinate
                OBJ_textureCoord this_textCoord;
                this_textCoord.lex(lexLine);
                this->textureCoords.push_back(this_textCoord);

            }else if (keyword=="vn"){ // normal vector
                OBJ_normal this_normal_vector;
                this_normal_vector.lex(lexLine);
                this->normals.push_back(this_normal_vector);

            }else if (keyword=="f"){ // triangle face
                OBJ_triFace this_triangle_face;
                this_triangle_face.lex(lexLine);
                this->triangleFaces.push_back(this_triangle_face);

            }else if (keyword=="mtllib"){ // material definition
                //std::cout << keyword << " material definition" << std::endl;

            }else if (keyword=="usemtl"){ // use material
                //std::cout << keyword << " use material" << std::endl;             

            }else{ // Comment or unsupported line..  Do nothing
                //std::cout << "Not Parsed" << std::endl;
            }
            
            
            
            //std::cout << keyword << std::endl; 
 
            
        }
        myfile.close();
    }
}
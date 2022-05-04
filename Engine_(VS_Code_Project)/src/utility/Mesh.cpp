#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> // used for stringstream
#include <algorithm> // used for std::remove_if() string ops
#include <filesystem>

#include "utility/Vec3d.h"
#include "utility/Triangle.h"
#include "utility/Mesh.h"




Mesh::Mesh(int mesh_id) {
	id = mesh_id;
}

std::vector<float> Mesh::stringToFloatVector(std::string input_string){
	input_string.erase(std::remove_if(input_string.begin(), input_string.end(), ::isspace), input_string.end());
	std::vector<float> tri_points;
	std::stringstream s_stream(input_string); //create string stream from the string
	while(s_stream.good()) {
		std::string substr;
		getline(s_stream, substr, ','); //get first string delimited by comma
		tri_points.push_back(std::stof(substr));
	}
				
	return tri_points;
} 

std::vector<Triangle>& Mesh::getTriangles(){
	return tris;
}

void Mesh::loadMesh(std::string filename){
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

		if (line.substr(0,2)!= comment) {
			// Line is not a comment
			if (line.back()!=linefeed && line.back()==';'){
				// Line is a properly formatted vector of 3D points for a triangle
				std::vector<float> tri_points;
				tri_points = stringToFloatVector(line); // convert to vector of floats
				// Add float vector values to a triangle using right hand rule
				Vec3d pt1(tri_points.at(0), tri_points.at(1), tri_points.at(2));
				Vec3d pt2(tri_points.at(3), tri_points.at(4),tri_points.at(5));
				Vec3d pt3(tri_points.at(6),tri_points.at(7),tri_points.at(8));
				Triangle this_tri(pt1, pt2, pt3, tri_id, color);
				Triangle that_tri=this_tri;

				add3dTriangle(that_tri);
				tri_id+=1;
			}else if (line.empty()){
				// Empty line, do nothing
			}else{
				std::cout<< "Bad line! " << line << std::endl;
			}

		}
		
    }
    myfile.close();
}

}

void Mesh::add3dTriangle(Triangle &this_tri){
	tris.push_back(this_tri);
}

void Mesh::performModifications(std::vector<std::shared_ptr<Triangle_Modifier>> triMods){

    for (auto triMod:triMods){
        for (auto &tri:tris){
            triMod->modifyTriangle(tri);   
        }
    }
}

void Mesh::performModifications(std::shared_ptr<Triangle_Modifier> triMod){
	for (auto &tri:tris){
		triMod->modifyTriangle(tri);
	}


}

void Mesh::setID(int in_id){
	id=in_id;
}

int Mesh::getID(){
	return id;
}

std::string Mesh::toString(){
    std::string ret_val;
	for (Triangle tri:tris){
		ret_val += tri.toString() + "\n";
	}
    
	return ret_val;
}	

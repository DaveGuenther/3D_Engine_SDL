#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> // used for stringstream
#include <algorithm> // used for std::remove_if() string ops
#include "Vec3d.h"
#include "Triangle.h"
#include "Mesh.h"
#include <filesystem>



Mesh::Mesh(void) {
	fTheta=45.0f;
	tTheta=45.0f;
}

float Mesh::get_fTheta(){
	return fTheta;
}

float Mesh::get_tTheta(){
	return tTheta;
}

void Mesh::Set_Rot_Angles(float fTheta_in, float tTheta_in){
	fTheta=fTheta_in;
	tTheta=tTheta_in;
}


std::vector<float> Mesh::string_to_float_vector(std::string input_string){
	/*
	This function will take a comma delimited string with no whitespace and return a vector of floats.
	input_string must be a comma delimited string of floats (eg: "1.0,2.1,3.4,1.6,-0.8,0.5")
	*/
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

std::vector<Triangle>& Mesh::get_tris(){
	return tris;
}

void Mesh::Load_Mesh(std::string filename){
	std::ifstream myfile;
	filename = "Meshes/"+filename;
	//std::cout << filename << std::endl;
	std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
	myfile.open (filename);

	if (myfile.is_open()) {
    std::string line;
	std::string comment = "//";
	char linefeed = '\n';
    int tri_id=0;
	while (std::getline(myfile, line)) {

		if (line.substr(0,2)!= comment) {
			// Line is not a comment
			if (line.back()!=linefeed && line.back()==';'){
				// Line is a properly formatted vector of 3D points for a triangle
				std::vector<float> tri_points;
				tri_points = string_to_float_vector(line); // convert to vector of floats

				/*for(int i = 0; i< tri_points.size(); i++) {    //print all vector values
					std::cout << tri_points.at(i) << std::endl;
				}*/
				// Add float vector values to a triangle using right hand rule
				Vec3d pt1(tri_points.at(0), tri_points.at(1), tri_points.at(2));
				Vec3d pt2(tri_points.at(3), tri_points.at(4),tri_points.at(5));
				Vec3d pt3(tri_points.at(6),tri_points.at(7),tri_points.at(8));
				Triangle this_tri(pt1, pt2, pt3, tri_id);
				Triangle that_tri=this_tri;
				//this_tri.setID(tri_id);
				add_3D_triangle(that_tri);
				tri_id+=1;
			}else if (line.empty()){
				// Empty line, do nothing
			}else{
				std::cout<< "Bad line! " << line << std::endl;
			}
			//std::cout << line.back() << std::endl;
		}
		
    }
    myfile.close();
}

}

void Mesh::add_3D_triangle(Triangle &this_tri){
	tris.push_back(this_tri);
}

void Mesh::PerformModifications(std::vector<Triangle_Modifier*> triMods){
	for (auto triMod:triMods){
		for (auto tri:tris){
			triMod->ModifyTri(tri);
		}
	}

}
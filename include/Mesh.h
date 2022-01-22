#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "Vec2d.h"
#include "Vec3d.h"
#include "Triangle.h"

class Mesh {

	private:
		std::vector<Triangle> tris; 		
		std::vector<float> string_to_float_vector(std::string input_string);
		void add_3D_triangle(Triangle this_tri);
				
	public:
		

		
		Mesh();
		void Load_Mesh(std::string filename);
		std::vector<Triangle> get_tris(); 
		

		
};

#endif
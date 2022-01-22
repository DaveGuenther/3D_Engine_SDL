#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "Vec2d.h"
#include "Vec3d.h"
#include "Triangle.h"

class Mesh {

		
	public:
		
		struct mesh_of_tris
		{
			std::vector<Triangle> tris;
		};

		Mesh();
		void Load_Mesh(std::string filename);
		std::vector<Triangle> get_tris(); 
		
	private: 		
		mesh_of_tris mesh;	

		std::vector<float> string_to_float_vector(std::string input_string);
		void add_3D_triangle(Triangle this_tri);
		
};

#endif
#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "vec2d.h"
#include "vec3d.h"

class Mesh {

		
	public:

		struct triangle
		{
			vec3d p[3];
		};
		
		struct mesh_of_tris
		{
			std::vector<triangle> tris;
		};

		Mesh();
		void Load_Mesh(std::string filename);
		std::vector<triangle> get_tris(); 
		
	private: 		
		mesh_of_tris mesh;	

		std::vector<float> string_to_float_vector(std::string input_string);
		void add_3D_triangle(vec3d pt1, vec3d pt2, vec3d pt3);
		
};

#endif
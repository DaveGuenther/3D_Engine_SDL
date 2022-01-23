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
		
		/**
		 * @brief fTheta and tTheta represent the current angles (in degrees) that this mesh will rotate during next refresh.  
		 * Both angles are set to 0.0f after a refresh is complete.
		 * 
		 */
		float fTheta, tTheta;

	public:
		

		
		Mesh();
		void Set_Rot_Angles(float fTheta_in, float tTheta_in);
		void Load_Mesh(std::string filename);
		std::vector<Triangle> get_tris(); 
		float get_fTheta();
		float get_tTheta();
		

		
};

#endif
#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "Vec2d.h"
#include "Vec3d.h"
#include "Triangle.h"
#include "Triangle_Modifier.h"

/**
 * @brief This class contains a single mesh object constructed of trianges in a 3D cartesian space.
 * 
 */
class Mesh {

	private:
		std::vector<Triangle> tris;
		
		/**
		 * @brief This function will take a comma delimited string of "floats" with no whitespace and return a vector of floats.  This method is used when loading a mesh from a file.
		 * 
		 * @param input_string input_string must be a comma delimited string of floats (eg: "1.0,2.1,3.4,1.6,-0.8,0.5")
		 * @return std::vector<float> 
		 */
		std::vector<float> string_to_float_vector(std::string input_string);

		/**
		 * @brief This method adds a Triangle object to the tris vector that makes up this class
		 * 
		 * @param this_tri A single Triangle object with points represented in the 3D cartesian space
		 */
		void add_3D_triangle(Triangle &this_tri);
		
		/**
		 * @brief fTheta and tTheta represent the current angles (in degrees) that this mesh will rotate during next refresh.  
		 * Both angles are set to 0.0f after a refresh is complete.
		 * 
		 */
		float fTheta, tTheta;

	public:
		

		
		Mesh();

		/**
		 * @brief This method assigns an x and z rotation angle in degrees for the mesh object to be rotated at the next Engine_3d::engine_update()
		 * 
		 * @param fTheta_in X Rotation Angle
		 * @param tTheta_in Z Rotation Angle
		 */
		void Set_Rot_Angles(float fTheta_in, float tTheta_in);

		/**
		 * @brief loads a proprietary .mesh file into the tris vector for this Mesh.  This method will eventually be replaced with functionality to read an stl file
		 * 
		 * @param filename std::string will be prefixed with "Meshes/" so the meshes will be housed in their own folder.
		 */
		void Load_Mesh(std::string filename);

		/**
		 * @brief Get a reference to the tris object.  May rewrite this to instead return an iterator to the vector.
		 * 
		 * @return std::vector<Triangle>& 
		 */
		std::vector<Triangle>& get_tris(); 

		
		void PerformModifications(std::vector<Triangle_Modifier*> triMods);

		/**
		 * @brief Get the fTheta object
		 * 
		 * @return float 
		 */
		float get_fTheta();

		/**
		 * @brief Get the tTheta object
		 * 
		 * @return float 
		 */
		float get_tTheta();
		

		
};

#endif
#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <memory>
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
		std::vector<float> stringToFloatVector(std::string input_string);

		/**
		 * @brief This method adds a Triangle object to the tris vector that makes up this class
		 * 
		 * @param this_tri A single Triangle object with points represented in the 3D cartesian space
		 */
		void add3dTriangle(Triangle &this_tri);
		
		/**
		 * @brief fTheta and tTheta represent the current angles (in degrees) that this mesh will rotate during next refresh.  
		 * Both angles are set to 0.0f after a refresh is complete.
		 * 
		 */
		
		int id;

	public:
		

		
		Mesh(int mesh_id);

		

		/**
		 * @brief loads a proprietary .mesh file into the tris vector for this Mesh.  This method will eventually be replaced with functionality to read an stl file
		 * 
		 * @param filename std::string will be prefixed with "Meshes/" so the meshes will be housed in their own folder.
		 */
		void loadMesh(std::string filename);

		/**
		 * @brief Get a reference to the tris object.  May rewrite this to instead return an iterator to the vector.
		 * 
		 * @return std::vector<Triangle>& 
		 */
		std::vector<Triangle>& getTriangles(); 

		/**
		 * @brief This function will accept a single Triangle_Modifier and will apply the modification (Rotation or Translation) on the selected meshes as determined by the Triangle_Modifier.getAssignedMeshIDs()
		 * 
		 * @param triMod This is a single Triangle_Modifier object (either a Translation or Rotation) which contains instructions on rotating all triangles in a number of meshes in the mesh pipeline
		 */
		void performModifications(std::shared_ptr<Triangle_Modifier> triMod);

		/**
		 * @brief Not used in the engine, and may be removed..  This function will accept a vector of Triangle_Modifiers and for each Triangle_Modifier, perform the modifications (Transformation or Rotation) of a list of meshes as determined in the Triangle_Modifier object.
		 * 
		 * @param triMods vector of Triangle_Modifiers (either a rotation or a translation) to be applied to meshes in the mesh pipeline
		 */
		void performModifications(std::vector<std::shared_ptr<Triangle_Modifier>> triMods);



		/**
		 * @brief Setter for the IID value of this Mesh
		 * 
		 * @param in_id 
		 */
		void setID(int in_id);
		
		/**
		 * @brief Getter function to retrieve the ID of this mesh
		 * 
		 * @return int 
		 */
		int getID();

		/**
		 * @brief This function returns a print friendly string of all Triangle information in this mesh.
		 * 
		 * @return std::string 
		 */
		std::string toString();
		
};

#endif
#ifndef TRIANGLE_MODIFIER_H
#define TRIANGLE_MODIFIER_H
#include <iostream>
#include <vector>
#include "Vec3d.h"
#include "Triangle.h"
#include "Mat4x4.h"

/**
 * @brief Abstract class that cannot be directly instantiated.  Instead please use Rotator or Translator when instantiating objects.  This abstract class enables the ability to either rotate or transform a mesh or list of meshes.
 * 
 */
class Triangle_Modifier{
    public: 
        /**
         * @brief Cannot instantiate directly.  Must use either Rotator or Translator
         * 
         * @param tri 
         */
        virtual void ModifyTri(Triangle &tri)=0;
        
        /**
         * @brief This function assigns the modifier to a particular mesh in the mesh pipeline identified by the mesh's ID value
         * 
         * @param mesh_id 
         */
        void AssignToMesh(int mesh_id);
        
        /**
         * @brief Get the vector of mesh_ids that have been assigned to this modifier.  This means that the modifier will end up modifying those mesh_ids
         * 
         * @return const std::vector<int> 
         */
        const std::vector<int> GetAssignedMeshIDs();
        
        

    protected:
        std::vector<int> mesh_ids;
        
};

/**
 * @brief The class directs rotation modifications to a list of meshes as directed by the object itself.  
 * 
 */
class Rotator: public Triangle_Modifier{
    private:
        float x_degs;
        float y_degs;
        float z_degs;
        Vec3d center_of_rotation;
        Mat4x4 mat_XRot;
        Mat4x4 mat_YRot;
        Mat4x4 mat_ZRot;
    public:
        /**
         * @brief This constructor accepts an x, y, and z angle in degrees to rotate the triangle by, and also a center of rotation (Vec3d) to apply to that triangle
         * 
         * @param x_degrees 
         * @param y_degrees 
         * @param z_degrees 
         * @param center 
         */
        Rotator(float x_degrees, float y_degrees, float z_degrees, Vec3d center);
        
        /**
         * @brief This function will accept the reference of a single triangle and conduct a rotation on that object in place.
         * 
         * @param tri 
         */
        void ModifyTri(Triangle &tri);


};

class Translator: public Triangle_Modifier{
    private:
        float x_dist;
        float y_dist;
        float z_dist;
    public:
        /**
         * @brief This constructor accepts an x, y, and z distance to move the triangle by.
         * 
         * 
         * @param x_distance 
         * @param y_distance 
         * @param z_distance 
         */
        Translator(float x_distance, float y_distance, float z_distance);
        /**
         * @brief This function will accept the reference of a single triangle and conduct a translation on that object in place.
         * 
         * @param tri 
         */
        void ModifyTri(Triangle &tri);


};

#endif
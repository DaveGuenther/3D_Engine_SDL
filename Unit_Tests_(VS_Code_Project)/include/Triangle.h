#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <string>
#include "Vec3d.h"


// Triangles are always defined in the 3D space
class Triangle{
    private:
        Vec3d p[3];
    
    public:
        
        Triangle();
        Triangle(const Vec3d &pt1, const Vec3d &pt2, const Vec3d &pt3);
        Triangle (const Triangle &T);

        /**
         * @brief Set a single point on the Triangle by it's right-hand (clockwise) position.
         * 
         * @param point: possible values are 0, 1, and 2 going in clockwise order looking at the face of the triangle head on
         * @param vec:  Vec3d value fo the point in 3d space
         */
        void setTrianglePoint(int point, const Vec3d &vec);
        Vec3d getTrianglePoint(int point);
        
        std::string toString();

        

    
};

#endif
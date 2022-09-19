#ifndef VEC3D_H
#define VEC3D_H

#if defined(PREDEF_PLATFORM_UNIX)
#   pragma message("Linux/Unix Platform Detected in Vec3d.h!")
#elif defined(PREDEF_PLATFORM_WINDOWS)
#   pragma message("Windows Platform Detected in Vec3d.h!")
#endif
#include <string>
#include <math.h>
#include "Vec2d.h"

/**
 * @brief This is a simply class mainly used as a data type.  It contains an X, Y, and Z coordinate.
 * 
 */
class Vec3d:public Vec2d{
  private:
    float z;
    float w;
    
  public:
    Vec3d();

    Vec3d(const float &x_in, const float &y_in, const float &z_in);

    Vec3d(const float &x_in, const float &y_in, const float &z_in, const float &w_in);

    Vec3d (const Vec3d &V);

    std::string toString();

    void setZ(const float &z_in);
    void setW(const float &w_in);
    

    const float& getZ()const;
    const float& getW()const;

    const Vec3d toThousandths();

  

    friend bool operator== (const Vec3d & vec1, const Vec3d & vec2);
    friend bool operator!= (const Vec3d & vec1, const Vec3d & vec2);
    
    friend Vec3d operator/ (const Vec3d& vec1, const Vec3d& vec2);
    friend Vec3d operator/ (const Vec3d& vec, const float& val);
    friend Vec3d operator/ (const float& val, const Vec3d& vec);
    
    
    friend Vec3d operator+ (const Vec3d& vec1, const Vec3d& vec2);
    friend Vec3d operator+ (const Vec3d& vec, const float& val);
    friend Vec3d operator+ (const float& val, const Vec3d& vec);
    
    
    friend Vec3d operator* (const Vec3d& vec1, const Vec3d& vec2);
    friend Vec3d operator* (const float& val, const Vec3d& vec);
    friend Vec3d operator* (const Vec3d& vec, const float& val);
    
    
    friend Vec3d operator- (const Vec3d& vec1, const Vec3d& vec2);
    friend Vec3d operator- (const Vec3d& vec, const float& val);
    friend Vec3d operator- (const float& val, const Vec3d& vec);
    
};

#endif
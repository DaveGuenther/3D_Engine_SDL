#ifndef VEC3D_H
#define VEC3D_H
#include "Vec2d.h"

class Vec3d:public Vec2d{
  private:
    float z;
    
  public:
    Vec3d(){ x=0.0f; y=0.0f; z=0.0f;}

    Vec3d(float x_in, float y_in, float z_in){
      x=x_in;
      y=y_in;
      z=z_in;
    }

    Vec3d (const Vec3d &V){
      x=V.x;
      y=V.y;
      z=V.z;
    }

    void print(){
      std::cout << "Vec3d (" << x << ", " << y << ", " << z << ")" << std::endl;
    }

    void setZ(float z_in){ z=z_in; }

    float getZ(){ return z; }
    
};

#endif
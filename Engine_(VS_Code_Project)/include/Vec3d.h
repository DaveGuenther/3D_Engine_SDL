#ifndef VEC3D_H
#define VEC3D_H
#include "Vec2d.h"

class Vec3d:public Vec2d{
  private:
    float z;
    
  public:
    Vec3d(){ x=0.0f; y=0.0f; z=0.0f;}

    Vec3d(const float &x_in, const float &y_in, const float &z_in){
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

    void setZ(const float &z_in){ z=z_in; }

    float getZ(){ return z; }
    
    friend bool operator== (const Vec3d & vec1, const Vec3d & vec2){ return (vec1.x==vec2.x && vec1.y==vec2.y && vec1.z==vec2.z);}

    friend bool operator!= (const Vec3d & vec1, const Vec3d & vec2){ return !(vec1.x==vec2.x && vec1.y==vec2.y && vec1.z==vec2.z);}
};

#endif
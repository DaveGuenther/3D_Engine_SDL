#ifndef VEC3D_H
#define VEC3D_H
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
    Vec3d(){ x=0.0f; y=0.0f; z=0.0f; w=1.0f; }

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

    std::string toString(){
      std::string ret_val = "Vec3d(" + std::to_string(x)+ ", "+std::to_string(y)+ ", "+std::to_string(z)+")";
      return ret_val;
    }

    void setZ(const float &z_in){ z=z_in; }
    void setW(const float &w_in){ w=w_in; }
    

    const float getZ()const { return z; }
    const float getW()const { return w; }

    Vec3d toThousandths(){
      return Vec3d(floor(this->x * 1000 + .5 )/1000, floor(this->y * 1000 + .5 )/1000, floor(this->z * 1000 + .5 )/1000);
    }

    friend bool operator== (const Vec3d & vec1, const Vec3d & vec2){ return (vec1.x==vec2.x && vec1.y==vec2.y && vec1.z==vec2.z);}
    friend bool operator!= (const Vec3d & vec1, const Vec3d & vec2){ return !(vec1.x==vec2.x && vec1.y==vec2.y && vec1.z==vec2.z);}
    
    friend Vec3d operator/ (const Vec3d& vec1, const Vec3d& vec2){ return Vec3d(vec1.getX()/vec2.getX(), vec1.getY()/vec2.getY(), vec1.getZ()/vec2.getZ());}
    friend Vec3d operator/ (const Vec3d& vec, const float& val){ return Vec3d(vec.getX()/val, vec.getY()/val, vec.getZ()/val);}
    friend Vec3d operator/ (const float& val, const Vec3d& vec){ return Vec3d(vec.getX()/val, vec.getY()/val, vec.getZ()/val);}
    
    
    friend Vec3d operator+ (const Vec3d& vec1, const Vec3d& vec2){ return Vec3d(vec1.getX()+vec2.getX(), vec1.getY()+vec2.getY(), vec1.getZ()+vec2.getZ()); }
    friend Vec3d operator+ (const Vec3d& vec, const float& val){ return Vec3d(val+vec.getX(), val+vec.getY(), val+vec.getZ()); }
    friend Vec3d operator+ (const float& val, const Vec3d& vec){ return Vec3d(val+vec.getX(), val+vec.getY(), val+vec.getZ()); }
    
    
    friend Vec3d operator* (const Vec3d& vec1, const Vec3d& vec2){ return Vec3d(vec1.getX()*vec2.getX(), vec1.getY()*vec2.getY(), vec1.getZ()*vec2.getZ()); }
    friend Vec3d operator* (const float& val, const Vec3d& vec){ return Vec3d(val*vec.getX(), val*vec.getY(), val*vec.getZ()); }
    friend Vec3d operator* (const Vec3d& vec, const float& val){ return Vec3d(val*vec.getX(), val*vec.getY(), val*vec.getZ()); }
    
    
    friend Vec3d operator- (const Vec3d& vec1, const Vec3d& vec2){ return Vec3d(vec1.getX()-vec2.getX(), vec1.getY()-vec2.getY(), vec1.getZ()-vec2.getZ()); }
    friend Vec3d operator- (const Vec3d& vec, const float& val){ return Vec3d(vec.getX()-val, vec.getY()-val, vec.getZ()-val); }
    friend Vec3d operator- (const float& val, const Vec3d& vec){ return Vec3d(vec.getX()-val, vec.getY()-val, vec.getZ()-val); }
    
};

#endif
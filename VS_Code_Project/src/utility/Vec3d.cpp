#if defined(PREDEF_PLATFORM_UNIX)
#   pragma message("Linux/Unix Platform Detected in Vec3d.cpp!")
#elif defined(PREDEF_PLATFORM_WINDOWS)
#   pragma message("Windows Platform Detected in Vec3d.cpp!")
#endif

#include "Vec3d.h"

Vec3d::Vec3d(){ x=0.0f; y=0.0f; z=0.0f; w=1.0f; }

Vec3d::Vec3d(const float &x_in, const float &y_in, const float &z_in){
    x=x_in;
    y=y_in;
    z=z_in;
    w=1.0f;
}

Vec3d::Vec3d(const float &x_in, const float &y_in, const float &z_in, const float &w_in){
    x=x_in;
    y=y_in;
    z=z_in;
    w=w_in;
}

Vec3d::Vec3d (const Vec3d &V){
    x=V.x;
    y=V.y;
    z=V.z;
    w=V.w;
}

std::string Vec3d::toString(){
    std::string ret_val = "Vec3d(" + std::to_string(x)+ ", "+std::to_string(y)+ ", "+std::to_string(z)+", "+std::to_string(w)+")";
    return ret_val;
}

//void Vec3d::setZ(const float &z_in){ z=z_in; }
//void Vec3d::setW(const float &w_in){ w=w_in; }


//const float& Vec3d::getZ()const { return z; }
//const float& Vec3d::getW()const { return w; }

const Vec3d Vec3d::toThousandths(){
    return Vec3d(floor(this->x * 1000 + .5 )/1000, floor(this->y * 1000 + .5 )/1000, floor(this->z * 1000 + .5 )/1000);
}



bool operator== (const Vec3d & vec1, const Vec3d & vec2){ return (vec1.x==vec2.x && vec1.y==vec2.y && vec1.z==vec2.z);}
bool operator!= (const Vec3d & vec1, const Vec3d & vec2){ return !(vec1.x==vec2.x && vec1.y==vec2.y && vec1.z==vec2.z);}

Vec3d operator/ (const Vec3d& vec1, const Vec3d& vec2){ return Vec3d(vec1.x/vec2.x, vec1.y/vec2.y, vec1.z/vec2.z);}
Vec3d operator/ (const Vec3d& vec, const float& val){ return Vec3d(vec.x/val, vec.y/val, vec.z/val);}
Vec3d operator/ (const float& val, const Vec3d& vec){ return Vec3d(val/vec.x, val/vec.y, val/vec.z);}


Vec3d operator+ (const Vec3d& vec1, const Vec3d& vec2){ return Vec3d(vec1.x+vec2.x, vec1.y+vec2.y, vec1.z+vec2.z); }
Vec3d operator+ (const Vec3d& vec, const float& val){ return Vec3d(val+vec.x, val+vec.y, val+vec.z); }
Vec3d operator+ (const float& val, const Vec3d& vec){ return Vec3d(val+vec.x, val+vec.y, val+vec.z); }

Vec3d operator* (const Vec3d& vec1, const Vec3d& vec2){ return Vec3d(vec1.x*vec2.x, vec1.y*vec2.y, vec1.z*vec2.z); }
Vec3d operator* (const float& val, const Vec3d& vec){ return Vec3d(val*vec.x, val*vec.y, val*vec.z); }
Vec3d operator* (const Vec3d& vec, const float& val){ return Vec3d(val*vec.x, val*vec.y, val*vec.z); }


Vec3d operator- (const Vec3d& vec1, const Vec3d& vec2){ return Vec3d(vec1.x-vec2.x, vec1.y-vec2.y, vec1.z-vec2.z); }
Vec3d operator- (const Vec3d& vec, const float& val){ return Vec3d(vec.x-val, vec.y-val, vec.z-val); }
Vec3d operator- (const float& val, const Vec3d& vec){ return Vec3d(val-vec.x, val-vec.y, val-vec.z); }

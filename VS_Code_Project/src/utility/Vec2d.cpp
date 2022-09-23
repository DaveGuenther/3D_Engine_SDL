#include "Vec2d.h"

Vec2d::Vec2d(){ x=0.0f; y=0.0f; uv_w=1.0f;}

Vec2d::Vec2d(const float &x_in, const float &y_in){
    x=x_in;
    y=y_in;
    uv_w=1.0f;
}

Vec2d::Vec2d(const float &x_in, const float &y_in, const float &w_in){
    x=x_in;
    y=y_in;
    uv_w=w_in;
}

Vec2d::Vec2d (const Vec2d &V){
    x=V.x;
    y=V.y;
    uv_w=V.uv_w;
}

//void Vec2d::setX(const float &x_in){ x=x_in; }
//void Vec2d::setY(const float &y_in){ y=y_in; }
//void Vec2d::setW(const float &w_in){ w=w_in; }

//const float& Vec2d::getX()const { return x; }
//const float& Vec2d::getY()const { return y; }
//const float& Vec2d::getW()const { return w; }

std::string Vec2d::toString(){
    std::string ret_val = "Vec2d(" + std::to_string(x)+ ", "+std::to_string(y)+ ", "+std::to_string(uv_w)+")";
    return ret_val;
}

bool operator== (const Vec2d & vec1, const Vec2d & vec2){ return (vec1.x==vec2.x && vec1.y==vec2.y&& vec1.uv_w==vec2.uv_w);}
bool operator!= (const Vec2d & vec1, const Vec2d & vec2){ return !(vec1.x==vec2.x && vec1.y==vec2.y && vec1.uv_w==vec2.uv_w);}
Vec2d operator+ (const Vec2d& vec1, const Vec2d& vec2){ return Vec2d(vec1.x+vec2.x, vec1.y+vec2.y, vec1.uv_w+vec2.uv_w); }
Vec2d operator- (const Vec2d& vec1, const Vec2d& vec2){ return Vec2d(vec1.x-vec2.x, vec1.y-vec2.y, vec1.uv_w-vec2.uv_w); }    
Vec2d operator* (const float& val, const Vec2d& vec){ return Vec2d(val*vec.x, val*vec.y, val*vec.uv_w); }
Vec2d operator* (const Vec2d& vec, const float& val){ return Vec2d(val*vec.x, val*vec.y, val*vec.uv_w); }
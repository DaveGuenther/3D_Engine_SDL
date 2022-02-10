#ifndef VEC2D_H
#define VEC2D_H
#include <string>


class Vec2d{
  public:
    Vec2d(){ x=0.0f; y=0.0f;}

    Vec2d(const float &x_in, const float &y_in){
      x=x_in;
      y=y_in;
    }

    Vec2d (const Vec2d &V){
      x=V.x;
      y=V.y;
    }

    void setX(const float &x_in){ x=x_in; }
    void setY(const float &y_in){ y=y_in; }

    float getX(){ return x; }
    float getY(){ return y; }

    std::string toString(){
      std::string ret_val = "Vec2d(" + std::to_string(x)+ ", "+std::to_string(y)+")";
      return ret_val;
    }

    friend bool operator== (const Vec2d & vec1, const Vec2d & vec2){ return (vec1.x==vec2.x && vec1.y==vec2.y);}
    friend bool operator!= (const Vec2d & vec1, const Vec2d & vec2){ return !(vec1.x==vec2.x && vec1.y==vec2.y);}

  protected:
		float x;
		float y;

};

#endif
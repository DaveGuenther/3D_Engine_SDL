#ifndef VEC2D_H
#define VEC2D_H
#include <iostream>

class Vec2d{
  public:
    Vec2d(){ x=0.0f; y=0.0f;}

    Vec2d(float x_in, float y_in){
      x=x_in;
      y=y_in;
    }

    Vec2d (const Vec2d &V){
      x=V.x;
      y=V.y;
    }

    void setX(float x_in){ x=x_in; }

    void setY(float y_in){ y=y_in; }

    float getX(){ return x; }

    float getY(){ return y; }

    void print(){
      std::cout << "Vec2d (" << x << ", " << y << ")" << std::endl;
    }

  protected:
		float x;
		float y;

};

#endif
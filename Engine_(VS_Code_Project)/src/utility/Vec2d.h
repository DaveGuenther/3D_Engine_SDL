#ifndef VEC2D_H
#define VEC2D_H
#include <string>

/**
 * @brief 
 * 
 */
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

    const float& getX()const { return x; }
    const float& getY()const { return y; }

    std::string toString(){
      std::string ret_val = "Vec2d(" + std::to_string(x)+ ", "+std::to_string(y)+")";
      return ret_val;
    }

    friend bool operator== (const Vec2d & vec1, const Vec2d & vec2){ return (vec1.x==vec2.x && vec1.y==vec2.y);}
    friend bool operator!= (const Vec2d & vec1, const Vec2d & vec2){ return !(vec1.x==vec2.x && vec1.y==vec2.y);}
    friend Vec2d operator+ (const Vec2d& vec1, const Vec2d& vec2){ return Vec2d(vec1.getX()+vec2.getX(), vec1.getY()+vec2.getY()); }
    friend Vec2d operator- (const Vec2d& vec1, const Vec2d& vec2){ return Vec2d(vec1.getX()-vec2.getX(), vec1.getY()-vec2.getY()); }    

  protected:
		float x;
		float y;

};

#endif
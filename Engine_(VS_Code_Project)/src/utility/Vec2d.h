#ifndef VEC2D_H
#define VEC2D_H
#include <string>

/**
 * @brief 
 * 
 */
class Vec2d{
  public:
    Vec2d(){ x=0.0f; y=0.0f; w=1.0f;}

    Vec2d(const float &x_in, const float &y_in){
      x=x_in;
      y=y_in;
      w=1.0f;
    }

    Vec2d(const float &x_in, const float &y_in, const float &w_in){
      x=x_in;
      y=y_in;
      w=w_in;
    }

    Vec2d (const Vec2d &V){
      x=V.x;
      y=V.y;
      w=V.w;
    }

    void setX(const float &x_in){ x=x_in; }
    void setY(const float &y_in){ y=y_in; }
    void setW(const float &w_in){ w=w_in; }

    const float& getX()const { return x; }
    const float& getY()const { return y; }
    const float& getW()const { return w; }

    std::string toString(){
      std::string ret_val = "Vec2d(" + std::to_string(x)+ ", "+std::to_string(y)+ ", "+std::to_string(w)+")";
      return ret_val;
    }

    friend bool operator== (const Vec2d & vec1, const Vec2d & vec2){ return (vec1.x==vec2.x && vec1.y==vec2.y&& vec1.w==vec2.w);}
    friend bool operator!= (const Vec2d & vec1, const Vec2d & vec2){ return !(vec1.x==vec2.x && vec1.y==vec2.y && vec1.w==vec2.w);}
    friend Vec2d operator+ (const Vec2d& vec1, const Vec2d& vec2){ return Vec2d(vec1.getX()+vec2.getX(), vec1.getY()+vec2.getY(), vec1.getW()+vec2.getW()); }
    friend Vec2d operator- (const Vec2d& vec1, const Vec2d& vec2){ return Vec2d(vec1.getX()-vec2.getX(), vec1.getY()-vec2.getY(), vec1.getW()-vec2.getW()); }    
    friend Vec2d operator* (const float& val, const Vec2d& vec){ return Vec2d(val*vec.getX(), val*vec.getY(), val*vec.getW()); }
    friend Vec2d operator* (const Vec2d& vec, const float& val){ return Vec2d(val*vec.getX(), val*vec.getY(), val*vec.getW()); }

  protected:
		float x;
		float y;
    float w; // used for perspective correction during texturemapping

};

#endif
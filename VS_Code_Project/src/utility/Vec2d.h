#ifndef VEC2D_H
#define VEC2D_H
#include <string>

/**
 * @brief 
 * 
 */
class Vec2d{
  public:
    Vec2d();

    Vec2d(const float &x_in, const float &y_in);

    Vec2d(const float &x_in, const float &y_in, const float &w_in);

    Vec2d (const Vec2d &V);

    //void setX(const float &x_in);
    void setY(const float &y_in);
    //void setW(const float &w_in);

    //const float& getX()const;
    const float& getY()const;
    //const float& getW()const;

    std::string toString();

    friend bool operator== (const Vec2d & vec1, const Vec2d & vec2);
    friend bool operator!= (const Vec2d & vec1, const Vec2d & vec2);
    friend Vec2d operator+ (const Vec2d& vec1, const Vec2d& vec2);
    friend Vec2d operator- (const Vec2d& vec1, const Vec2d& vec2);    
    friend Vec2d operator* (const float& val, const Vec2d& vec);
    friend Vec2d operator* (const Vec2d& vec, const float& val);

    float x;
    float uv_w; // used for perspective correction during texturemapping

  protected:
		
		float y;

};

#endif
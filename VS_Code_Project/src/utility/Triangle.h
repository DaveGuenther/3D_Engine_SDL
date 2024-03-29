#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "Vec3d.h"
#include "../materials/TexturePNG.h"


/**
 * @brief This class contains a single triangle made up of three enumerated Vec3ds (0, 1, and 2) defined in clockwise order.
 * 
 */
class Triangle{

    public:
        
        Triangle();
        Triangle(const Vec3d &pt1, const Vec3d &pt2, const Vec3d &pt3, const int &triangle_id);
        Triangle(const Vec3d &pt1, const Vec3d &pt2, const Vec3d &pt3, const int &triangle_id, const SDL_Color this_color);
        Triangle(const Vec3d &pt1, const Vec3d &pt2, const Vec3d &pt3, const Vec2d &tex_p1, const Vec2d &tex_p2, const Vec2d &tex_p3, const int &triangle_id, const SDL_Color this_color, const float dim_amount, std::shared_ptr<TexturePNG> this_texture_ptr);

        Triangle (const Triangle &T);

        /**
         * @brief Set a single point on the Triangle by it's right-hand (clockwise) position.
         * 
         * @param point: possible values are 0, 1, and 2 going in clockwise order looking at the face of the triangle head on
         * @param vec:  Vec3d value fo the point in 3d space
         */
        void setTrianglePoint(int point, const Vec3d &vec);

        void setUVPoint(int point, const Vec2d &vec);
        
        /**
         * @brief this function provides an id value for this triangle in the mesh.  It isn't readily used by the engine except to print the triangle string.
         * 
         * @param tri_id 
         */
        void setID(int tri_id);

        void setTexture(std::shared_ptr<TexturePNG> texture);

        void setColor(SDL_Color this_color);

        void setLightDimAmount(float lightDim);
        const float& getLightDimAmount();
        /**
         * @brief Get a single point of a ttriangle.  Given an enumerated point (0, 1, or 2), this function will return the Vec3d value.
         * 
         * @param point 
         * @return Vec3d 
         */
        const Vec3d& getTrianglePoint(int point);
        const Vec2d& getUVPoint(int point);
        const float getTriangleZCenter();
        const float getInverseDistanceToCamera(Vec3d camera_pos);
        const int getID();

        void setUnitNormalFromPoints();
        const Vec3d& getUnitNormalVector();
        const SDL_Color& getColor();
        std::shared_ptr<TexturePNG> getTexture();
        TexturePNG* getTextureRawPtr();
        const std::string toString();



    private:
        const float getTriangleYCenter();
        const float getTriangleXCenter();
        const Vec3d getTriangleCenter();
        Vec3d unit_normal_vector;
        Vec3d p[3];
        Vec2d textureCoords[3];
        float distance_to_player_camera;
        int tri_id;
        SDL_Color color;
        float dim_amount; // float form 0.0 to 1.0 that is multiplied against each color used to draw the triangle
        std::shared_ptr<TexturePNG> texture_ptr;
    
};

#endif
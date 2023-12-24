#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include "../utility/Vec3d.h"
#include "../utility/Mat4x4.h"
#include "../render/Frustum.h"


/**
 * @brief This camera class allows a camera to be places anywhere in the 3D world and moved around/turned.  From that point it projects to the screen.  It has two major aspects
 * - the "camera" vector that has it's current position relative to 0,0,0
 * - the "lookVector", which is a unit vector that points to the direction that the camera will face when rendering the scene
 * 
 * To use the camera, we will always start with the camera facing Z-forward at the beginning of each cycle (0,0,1).  Then we'll rotate around X and Y axis the total pitch and yaw
 * amounts from input.  Pitch and yaw are additive.  Each cycle you add/subtract the values from their previous value in order to have a pitch_total and yaw_total to rotate starting
 * at z-forward.  After rotating the camera and storing into lookVector, you add lookVector to the camera's position vector "camera" in order to get a target for rendering
 * 
 */
class Camera{
    public:
        
        /**
         * @brief Construct a new Camera object
         * 
         * @param aspectRatio is required to build the frustum 
         */
        Camera(float aspectRatio, float max_draw_dist, float FOV);
        Mat4x4 buildViewMatrix();
        
        
        /**
         * @brief Set the Camers position in world space.  This moves the camera from the direction that the camera is facing, not absolute X, Y, and Z axis movement.
         * 
        * @param pos_vector Vec3d that represents the left/right, up/down, forward/backward amount to mov the camera with respect to the direction that the camera is facing
         */
        void setCameraPos(Vec3d pos_vector);
        
        //void setCameraDir(Vec3d dir_vector);
        
        /**
         * @brief This method rotates the camera around the X and Y axis from the z-forward direction (0,0,1).  The rotation vector lookVector is the new direction and is a unit vector
         * 
         * @param rotation_vector this is a Vec3d that contains pitch and yaw information in degrees.  Vec3d (pitch, yaw, 0).  There is no Z rotation (roll) implemented.
         * Pitch is the degrees to look up or down (positive degrees points the camera up, rotation the environment effectively down)
         * Yaw is the degrees to look left or right (positive degrees points the camera right, rotation the environment effectively left)
         */
        void rotateCamera(Vec3d rotation_vector);
        
        /**
         * @brief Get the Camera Position object in world space 
         * 
         * @return Vec3d (x, y, z)
         */
        Vec3d getCameraPos();
        
        std::shared_ptr<Frustum> cameraViewFrustum;
        //Frustum* cameraViewFrustum;

        /**
         * @brief Gets the camera's maximum z draw distance (relative to the camera's position and direction)
         * This information is also used to help dim triangles as we go further back
        */
        float getMaxDrawDist();

    private:
        /**
         * @brief creates a new "point at" vector for the camera to render by adding the camera's current position vector and the direction unit vector.
         * 
         * @return Vec3d 
         */
        Vec3d calc_vTarget();
        Vec3d vTarget; // Camera's new direction that it should face at the end of the frame
        Vec3d camera; // Camera's x, y, and z position in world space
        Vec3d lookVector; // Camera's original look direction (x, y, z) unit vector
        float pitch_total=0.0f; // Amount of rotation around X axis (pitch the camera up and down)
        float yaw_total=0.0f; // Amount of rotation around the Y axis (turn the camera left or right)
        //Vec3d frustum_top_normal, frustum_bottom_normal, frustum_left_normal, frustum_right_normal;
        float maxDrawDist;
};

#endif
#ifndef ACTION_INTERFACE_H
#define ACTION_INTERFACE_H

#include <string>
#include <unordered_map>
#include <memory>
#include "utility/Triangle_Modifier.h"
#include "render/Camera.h"

enum ActionCommandState {OFF, TRIG_ATTACK, ATTACK, SUSTAIN, TRIG_RELEASE, RELEASE};

/*
Notes to self..  There are several types of actions:
- Actions that start and finish in a single frame (look)
- Actions that are executed on a key_stroke and cannot be retriggered until the current instance is completed (jump)
- Actions that are executed as long as a key is pressed (walk, strafe)
- Actions that are executed through some other event (some sort of physics action line being pushed or gravity -- simply falling off a platform or coming down from a jump)
*/

/**
 * @brief This is an Interface for Actions in the Engine that may cause mesh modifications (walk, jump, look)  It is called mostly by Action_Updater class
 * 
 */
class IAction{
    public:

        /**
         * @brief Some actions will live as long as the engine is running and can be retriggered after completion, 
         * while other actions are instantaneous like MouseLook actions will resolve and be detroyed at the end of a single frame.  
         * This method will take an action that will require multiple frames to complete and trigger it so that update() will advance it through it's lifespan
         * 
         */
        void trigger();

        /**
         * @brief this method will advance an action and apply and mesh/triangle modifications needed for this frame.  It is called for each frame until it is in a complete/OFF state 
         * 
         * @param key_pressed used only when the action needs to determine if a key press/hold is required for it to stay active (walk forward, strafe left, are all examples of actions that take into considerations if a key is held down)
         */
        virtual void update(bool key_pressed)=0;

        //const bool isComplete();


        /**
         * @brief returns true if the action is currently running, otherwise it retruns false.  This is used for actions that exist for more than one frame
         * 
         * @return true 
         * @return false 
         */
        const bool isRunning();

        /**
         * @brief This is used mostly for actions that are instantaneous (the are created and destroyed in a single frame).  
         * It is true once the action is complete and can be removed from the game's action_map
         * 
         * @return true 
         * @return false 
         */
        const bool isReadyToDestroy();

        const std::string getName();

        /**
         * @brief Get the Mesh Modification object.  The mesh modifications are applied in the Action_Updater class
         * 
         * @return std::shared_ptr<Triangle_Modifier> 
         */
        std::shared_ptr<Triangle_Modifier> getMeshModification() const;
    protected: 
        bool is_running;
        bool is_key_pressed;
        std::string command_name;
        bool readyToDestroy;
        std::string name;
        std::shared_ptr<Triangle_Modifier> mesh_modification;
        std::shared_ptr<Camera> this_camera;
};

class TurnAction:public IAction{
    public:
    TurnAction(std::string command_name, std::shared_ptr<Camera> this_camera, Vec3d direction_unit_vector);
    void update(bool key_pressed);

    private: 
    Vec3d direction_unit_vector;
};

class UseAction:public IAction{
    public:
    UseAction(std::string command_name, std::shared_ptr<Camera> this_camera);
    void update(bool key_pressed);    
};

/**
 * @brief Concrete implementation of IAction that handles a jump event.
 * 
 */
class JumpAction:public IAction{
    public:
    JumpAction(std::string command_name, std::shared_ptr<Camera> this_camera);
    void update(bool key_pressed);
};

/**
 * @brief Concrete implementation of IAction that handles a mouse_look event
 * 
 */
class TwoAxisRangeCommand:public IAction{
    private:
        float x_range;
        float y_range;
        

    public:
        /**
         * @brief Construct a new Two Axis Range Command object
         * 
         * @param command_name 
         * @param x_range is the delta_x angle that will apply to all meshes for rotation
         * @param y_range is the delta_y angle that will apply to all meshes for rotation
         */
        TwoAxisRangeCommand(std::string command_name, std::shared_ptr<Camera> this_camera, float x_range, float y_range);
        ~TwoAxisRangeCommand();
        /**
         * @brief Needs further development...  Will eventually work such that the jump just propels the character into the air and a 
         * separate gravity object will pull the character back down.
         * 
         * @param key_pressed 
         */
        void update(bool key_pressed);

};

/**
 * @brief Concrete implementation for IAction that handles movement based on a key being pressed/held down.  This class also implements an ASR envelope (Attack, Sustain, Release).
 * This makes it so when movement is initiated, the player gradually speeds up into the movement from being still once the key is pressed, eventually reaches a maximum speed when the key
 * continues to be held down, and gradually slows to a stop once the key is released.
 * 
 */
class MoveAction:public IAction{
    private:

        float attack_speed_delta, release_speed_delta;
        float speed; // 0.0-1.0  0.0 is stopped, 1.0 is full speed
        float max_speed; // m/s
        float FPS;
        ActionCommandState action_state;
        
        /**
         * @brief Set the Action State object.  This is called by the update() method and is used to manage state (including transitions) from Attack, Sustain, Release, and Off
         * 
         */
        void setActionState();
        
        /**
         * @brief This is a unit vec3d that tells the engine what direction to apply the mesh/triangle modifications
         * 
         */
        Vec3d direction;
        

    public:
        /**
         * @brief Construct a new Move Action object
         * 
         * @param command_name string name of the command
         * @param direction unit vector to tell this class what direction the triangle modifications will occur
         * @param attack time (seconds) to be spent in attack (speeding up or fading in)
         * @param release time (seconds) to be spent in release (slowing down or fading out)
         * @param max_speed total speed that will apply once the action is in sustain state
         * @param FPS Target engine frames per second (default is 60.0)
         */
        MoveAction(std::string command_name, std::shared_ptr<Camera> this_camera, Vec3d direction, float attack, float release, float max_speed, float FPS);
        ~MoveAction();
        void setAttack(float attack);
        void setRelease(float release);
        void update(bool key_pressed);
        
        
};
#endif
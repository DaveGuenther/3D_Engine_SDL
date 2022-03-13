#ifndef ACTION_INTERFACE_H
#define ACTION_INTERFACE_H

#include <string>
#include <unordered_map>


enum ActionCommandState {OFF, TRIG_ATTACK, ATTACK, SUSTAIN, TRIG_RELEASE, RELEASE};

class IAction{
    public:
        void trigger();
        virtual void update(bool key_pressed)=0;
        const bool isComplete();
        const bool isRunning();
        const bool isReadyToDestroy();
        const std::string getName();
    protected: 
        bool is_running;
        bool is_key_pressed;
        std::string command_name;
        bool readyToDestroy;
        std::string name;
};

class TwoAxisRangeCommand:public IAction{
    private:
        float x_range;
        float y_range;
        

    public:
        TwoAxisRangeCommand(std::string command_name, float x_range, float y_range);
        void update(bool key_pressed);

};

class MoveAction:public IAction{
    private:

        float attack_speed_delta, release_speed_delta;
        float speed; // 0.0-1.0  0.0 is stopped, 1.0 is full speed
        float max_speed; // m/s
        float FPS;
        ActionCommandState action_state;
        void setActionState();
        

    public:
        MoveAction(std::string command_name, float attack, float release, float max_speed, float FPS);
        void setAttack(float attack);
        void setRelease(float release);
        void update(bool key_pressed);

};
#endif
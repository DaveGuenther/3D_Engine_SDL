#ifndef ACTION_UPDATER_H
#define ACTION_UPDATER_H

#include <unordered_map>
#include "actions/Action_Interface.h"
#include <string>

class Action_Updater{
    public:
    Action_Updater(int FPS);
    void AddTactileInputMap(const std::unordered_map<std::string,bool> &input_tactile_map);
    void AddRangeInputMap(const std::unordered_map<std::string,float> &input_range_map);
    void update();

    private:
    int numberOfActiveCommands(const std::unordered_map<std::string, IAction*> &action_map) const;
    int FPS;
    std::unordered_map<std::string, IAction*> action_map;
    std::unordered_map<std::string,bool> input_tactile_map;
    std::unordered_map<std::string,float> input_range_map;
};

#endif
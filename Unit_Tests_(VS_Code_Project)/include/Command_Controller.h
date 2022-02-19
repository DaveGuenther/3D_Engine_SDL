#ifndef HUMAN_INPUT_H
#define HUMAN_INPUT_H

#include <unordered_map>
#include <string>

class Controller_Commands{
    public:
    virtual void updateCommandMap(std::unordered_map<std::string, std::string>& command_map)=0;

};

class KeyboardCommands: public Controller_Commands{
    public:
    void updateCommandMap(std::unordered_map<std::string, std::string>& command_map){
        
    }
};

#endif
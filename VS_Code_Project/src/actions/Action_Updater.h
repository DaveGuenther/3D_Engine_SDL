#ifndef ACTION_UPDATER_H
#define ACTION_UPDATER_H

#include <unordered_map>
#include <string>
#include <memory>

#include "../actions/Action_Interface.h"
#include "../utility/Triangle_Modifier.h"
#include "../utility/Mesh_Pipeline.h"
#include "../render/Camera.h"
#include "../core/Console_Variables.h"


class IAction_Updater{
    public:
    virtual void update()=0;    
    void AddTactileInputMap(const std::unordered_map<std::string,bool> &input_tactile_map);
    void AddRangeInputMap(const std::unordered_map<std::string,float> &input_range_map, const bool didRangeInputChange);
    
    protected:
    int numberOfActiveCommands(const std::unordered_map<std::string, IAction*> &action_map) const;
    int FPS;
    std::unordered_map<std::string, IAction*> action_map;
    std::unordered_map<std::string,bool> input_tactile_map;
    std::unordered_map<std::string,float> input_range_map;
    bool didRangeInputChange;
    ConsoleData* consoleData;


};

class InGame_Action_Updater: public IAction_Updater{
    public:

    InGame_Action_Updater(std::shared_ptr<Mesh_Pipeline> mesh_pipeline, std::shared_ptr<Camera> this_camera, int FPS, GameStateSubject &subject, ConsoleData* my_console_data);
    std::vector<std::shared_ptr<Triangle_Modifier>> getModifications() const; // This should be the Mesh_Pipeline actiually
    void update();

    private:

    std::vector<std::shared_ptr<Triangle_Modifier>> modifications;  
    std::shared_ptr<Mesh_Pipeline> mesh_pipeline;
    std::shared_ptr<Camera> this_camera;

};

class Console_Action_Updater: public IAction_Updater{
    public:

    Console_Action_Updater(GameStateSubject &subject, ConsoleData* my_console_data);
    void logConsoleCommand(std::string my_command);
    void update();

    private:
    ConsoleData* consoleData;
    std::string console_command;
    
};

#endif
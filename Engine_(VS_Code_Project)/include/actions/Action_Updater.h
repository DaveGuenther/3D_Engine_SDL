#ifndef ACTION_UPDATER_H
#define ACTION_UPDATER_H

#include <unordered_map>
#include "actions/Action_Interface.h"
#include "Triangle_Modifier.h"
#include "Mesh_Pipeline.h"
#include <string>

class IAction_Updater{
    public:
    virtual void update()=0;    
    void AddTactileInputMap(const std::unordered_map<std::string,bool> &input_tactile_map);
    void AddRangeInputMap(const std::unordered_map<std::string,float> &input_range_map);
    
    protected:
    int numberOfActiveCommands(const std::unordered_map<std::string, IAction*> &action_map) const;
    int FPS;
    std::unordered_map<std::string, IAction*> action_map;
    std::unordered_map<std::string,bool> input_tactile_map;
    std::unordered_map<std::string,float> input_range_map;


};

class InGame_Action_Updater: public IAction_Updater{
    public:
    //InGameActionUpdater(int FPS);
    InGame_Action_Updater(Mesh_Pipeline* mesh_pipeline, int FPS);
    //void AddTactileInputMap(const std::unordered_map<std::string,bool> &input_tactile_map);
    //void AddRangeInputMap(const std::unordered_map<std::string,float> &input_range_map);

    std::vector<Triangle_Modifier*> getModifications() const; // This should be the Mesh_Pipeline actiually
    


    void update();

    private:
    //int numberOfActiveCommands(const std::unordered_map<std::string, IAction*> &action_map) const;
    int FPS;
    //std::unordered_map<std::string, IAction*> action_map;
    //std::unordered_map<std::string,bool> input_tactile_map;
    //std::unordered_map<std::string,float> input_range_map;
    std::vector<Triangle_Modifier*> modifications;  
    Mesh_Pipeline* mesh_pipeline;
    

};

#endif
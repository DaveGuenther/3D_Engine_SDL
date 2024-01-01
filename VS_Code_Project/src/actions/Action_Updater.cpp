#include <vector>
#include <iostream>
#include <memory>

#include "Action_Updater.h"
#include "Action_Interface.h"


void IAction_Updater::AddTactileInputMap(const std::unordered_map<std::string,bool> &input_tactile_map){
    this->input_tactile_map=input_tactile_map;
}

void IAction_Updater::AddRangeInputMap(const std::unordered_map<std::string,float> &input_range_map, const bool didRangeInputChange){
    this->input_range_map = input_range_map;
    this->didRangeInputChange=didRangeInputChange;
}

/**
 * @brief Gets the number of Commands that are being processed in the map
 * 
 * @param action_map 
 * @return int 
 */
int IAction_Updater::numberOfActiveCommands(const std::unordered_map<std::string, IAction*> &action_map) const{
    int number_of_active_actions=0;
    std::unordered_map<std::string, IAction*>::const_iterator it = action_map.begin();
    while (it!=action_map.end()){
        if (it->second->isRunning()) { number_of_active_actions+=1; }
        it++;
    }
    return number_of_active_actions;
}



InGame_Action_Updater::InGame_Action_Updater(std::shared_ptr<Mesh_Pipeline> mesh_pipeline, std::shared_ptr<Camera> this_camera, int FPS, GameStateSubject &subject, ConsoleData* my_console_data){
    this->consoleData = my_console_data;
    this->this_camera= this_camera;
    action_map.insert_or_assign("MOVE_FORWARD", new MoveAction("MOVE_FORWARD", this_camera, Vec3d{0,0,1}, 1.0f, 1.0f, 0.1f, FPS, my_console_data));
    action_map.insert_or_assign("MOVE_BACKWARD", new MoveAction("MOVE_BACKWARD", this_camera, Vec3d{0,0,-1}, 1.0f, 1.0f, 0.1f, FPS, my_console_data));
    action_map.insert_or_assign("STRAFE_LEFT", new MoveAction("STRAFE_LEFT", this_camera, Vec3d{-1,0,0}, 1.0f, 1.0f, 0.1f, FPS, my_console_data));
    action_map.insert_or_assign("STRAFE_RIGHT", new MoveAction("STRAFE_RIGHT", this_camera, Vec3d{1,0,0}, 1.0f, 1.0f, 0.1f, FPS, my_console_data));
    action_map.insert_or_assign("LOOK_LEFT",new TurnAction("LOOK_LEFT",this_camera, Vec3d(0,-1,0), my_console_data));
    action_map.insert_or_assign("LOOK_RIGHT",new TurnAction("LOOK_RIGHT",this_camera, Vec3d(0,1,0), my_console_data));
    action_map.insert_or_assign("LOOK_UP",new TurnAction("LOOK_UP",this_camera, Vec3d(-1,0,0), my_console_data));
    action_map.insert_or_assign("LOOK_DOWN",new TurnAction("LOOK_DOWN",this_camera, Vec3d(1,0,0), my_console_data));
    action_map.insert_or_assign("USE", new UseAction("USE", this_camera, my_console_data));
    action_map.insert_or_assign("QUIT", new GameStateAction("QUIT",subject, my_console_data));
    //action_map.insert_or_assign("LOOK_LEFT", new TwoAxisRangeCommand("LOOK_LEFT", this_camera, -0.1f,0.0f));
    action_map.insert_or_assign("JUMP", new MoveAction("JUMP", this_camera, Vec3d{0,1,0}, 1.0f, 1.0f, 0.5f, FPS, my_console_data));
    action_map.insert_or_assign("CROUCH", new MoveAction("CROUCH", this_camera, Vec3d{0,-1,0}, 1.0f, 1.0f, 0.5f, FPS, my_console_data));
    //std::shared_ptr<Mesh_Pipeline> local_mesh_pipeline()
    action_map.insert_or_assign("CONSOLE", new GameStateAction("CONSOLE", subject, my_console_data));
    this->mesh_pipeline = mesh_pipeline;  // I know this is bad coding practice and tightly couples code..  Not sure how else to do it yet.  I might eventually try some kind of observer where ActionUpdater is the subject and mesh_pipeline is the observer, updating itself when the time comes...
    
}

void InGame_Action_Updater::update(){
    modifications.clear();
    //  Translate lexd input to input commands
    for (auto input:input_tactile_map){ 
        
        action_map.at(input.first)->trigger(); 
    
    } // Tactile Input
    float prev_range_x, prev_range_y, range_x, range_y;
    int mouse_x, mouse_y, prev_mouse_x, prev_mouse_y;
    for (auto range_input:input_range_map) {  
        if (range_input.first.find("MOUSE_X_DELTA") != std::string::npos){ range_x=range_input.second; }
        if (range_input.first.find("MOUSE_Y_DELTA") != std::string::npos){ range_y=range_input.second; }
    }
    if (this->didRangeInputChange){
        
        
        action_map.insert_or_assign("LOOK_XY", new TwoAxisRangeCommand("LOOK_XY", this_camera, range_x, range_y, this->consoleData));
    }
    prev_mouse_x=mouse_x;
    prev_mouse_y=mouse_y;

    // for each active command, update the command's action loop
    int num_commands_active = numberOfActiveCommands(action_map);
    if (num_commands_active>0){
        std::vector<std::string> destroyable_commands;
        for (auto command:action_map){
            if (command.second->isRunning()) { 
                // Find a way to look through input_map.first to find out if command.first is MISSING from it  If so, command.second->release().  
                // Then update.  It's the only way to identify that a key release occurred
                std::string command_to_find = command.first;
                if (input_tactile_map.find(command_to_find) != input_tactile_map.end()) { 
                    // Key for command is still pressed
                    command.second->update(true);  
                } else { 
                    // key for command is no longer pressed
                    command.second->update(false); 
                }                        
            }
            if (command.second->isReadyToDestroy()) { 
                destroyable_commands.push_back(command.second->getName()); 
            }
            
        }
        std::cout << std::endl;
        
        //Add modifications to tri_modifier
        for (auto this_command:action_map){
            
            if (this_command.second->getMeshModification()!=NULL){
                std::shared_ptr<Triangle_Modifier> this_mod = this_command.second->getMeshModification();
                for(int i=0;i<mesh_pipeline->GetSize();i++){ this_mod->assignToMesh(i); }
                modifications.push_back(this_command.second->getMeshModification());
                //for(int i=0;i<mesh_pipeline->GetSize();i++){ modifications.back().assignToMesh(i); }
            }
        }


        // clean up action_map and destroy completed objects;
        for (auto this_command_name:destroyable_commands){
            action_map.erase(this_command_name);
        }           
        
    }

}

std::vector<std::shared_ptr<Triangle_Modifier>> InGame_Action_Updater::getModifications() const{
    return this->modifications;
}

Console_Action_Updater::Console_Action_Updater(GameStateSubject &subject, ConsoleData* my_console_data){
    this->consoleData = my_console_data;
    action_map.insert_or_assign("BACK_TO_GAME", new GameStateAction("BACK_TO_GAME", subject, my_console_data));
}

void Console_Action_Updater::update(){
    
    //  Translate lexd input to input commands
    for (auto input:input_tactile_map){ 
        
        action_map.at(input.first)->trigger(); 
    
    } // Tactile Input
    

    // for each active command, update the command's action loop
    int num_commands_active = numberOfActiveCommands(action_map);
    if (num_commands_active>0){
        std::vector<std::string> destroyable_commands;
        for (auto command:action_map){
            if (command.second->isRunning()) { 
                // Find a way to look through input_map.first to find out if command.first is MISSING from it  If so, command.second->release().  
                // Then update.  It's the only way to identify that a key release occurred
                std::string command_to_find = command.first;
                if (input_tactile_map.find(command_to_find) != input_tactile_map.end()) { 
                    // Key for command is still pressed
                    command.second->update(true);  
                } else { 
                    // key for command is no longer pressed
                    command.second->update(false); 
                }                        
            }
            if (command.second->isReadyToDestroy()) { 
                destroyable_commands.push_back(command.second->getName()); 
            }
            
        }
        std::cout << std::endl;
        
        // clean up action_map and destroy completed objects;
        for (auto this_command_name:destroyable_commands){
            action_map.erase(this_command_name);
        }           
        
    }

}
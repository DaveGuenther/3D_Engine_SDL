#include "actions/Action_Updater.h"
#include "actions/Action_Interface.h"
#include <vector>
#include <iostream>

void IAction_Updater::AddTactileInputMap(const std::unordered_map<std::string,bool> &input_tactile_map){
    this->input_tactile_map=input_tactile_map;
}

void IAction_Updater::AddRangeInputMap(const std::unordered_map<std::string,float> &input_range_map){
    this->input_range_map = input_range_map;
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



InGame_Action_Updater::InGame_Action_Updater(Mesh_Pipeline* mesh_pipeline, int FPS){
    action_map.insert_or_assign("MOVE_FORWARD", new MoveAction("MOVE_FORWARD", Vec3d{0,0,-1}, 1.0f, 1.0f, 0.5f, FPS));
    action_map.insert_or_assign("MOVE_BACKWARD", new MoveAction("MOVE_BACKWARD", Vec3d{0,0,1}, 1.0f, 1.0f, 0.5f, FPS));
    action_map.insert_or_assign("STRAFE_LEFT", new MoveAction("STRAFE_LEFT", Vec3d{1,0,0}, 1.0f, 1.0f, 0.5f, FPS));
    action_map.insert_or_assign("STRAFE_RIGHT", new MoveAction("STRAFE_RIGHT", Vec3d{-1,0,0}, 1.0f, 1.0f, 0.5f, FPS));
    action_map.insert_or_assign("JUMP", new JumpAction("JUMP"));
    this->mesh_pipeline = mesh_pipeline;  // I know this is bad coding practice and tightly couples code..  Not sure how else to do it yet.  I might eventually try some kind of observer where ActionUpdater is the subject and mesh_pipeline is the observer, updating itself when the time comes...

}

void InGame_Action_Updater::update(){
    modifications.clear();
    //  Translate parsed input to input commands
    for (auto input:input_tactile_map){ 
        
        action_map.at(input.first)->trigger(); 
    
    } // Tactile Input
    float prev_range_x, prev_range_y, range_x, range_y;
    for (auto range_input:input_range_map) {  
        if (range_input.first.find("MOUSE_X_DELTA") != std::string::npos){ range_x=range_input.second; }
        if (range_input.first.find("MOUSE_Y_DELTA") != std::string::npos){ range_y=range_input.second; }
    }
    if (range_x>0.00001||range_y>0.00001){
        
        //NEED TO Uncomment this eventully to allow mouse input once keys are working...
        //action_map.insert_or_assign("LOOK_XY", new TwoAxisRangeCommand("LOOK_XY", range_x, range_y));
    }

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
                Triangle_Modifier* this_mod = this_command.second->getMeshModification();
                for(int i=0;i<mesh_pipeline->GetSize();i++){ this_mod->AssignToMesh(i); }
                modifications.push_back(this_command.second->getMeshModification());
                //for(int i=0;i<mesh_pipeline->GetSize();i++){ modifications.back().AssignToMesh(i); }
            }
        }


        // clean up action_map and destroy completed objects;
        for (auto this_command_name:destroyable_commands){
            action_map.erase(this_command_name);
        }           
        
    }

}

std::vector<Triangle_Modifier*> InGame_Action_Updater::getModifications() const{
    return this->modifications;
}
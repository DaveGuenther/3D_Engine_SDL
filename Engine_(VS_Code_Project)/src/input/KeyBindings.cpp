#include "input/KeyBindings.h"
#include <string>
#include <unordered_map>
#include <filesystem> // loading key bindings
#include <fstream>
#include <algorithm>
#include <iostream>


std::string Bindings::getCommand(std::string key_code){
    std::string command;
    std::unordered_map<std::string,std::string>::iterator it; 
    it = bindings.find(key_code);
    if (it!=bindings.end()){ command=bindings.at(key_code); } else { command="NA"; }
    return command;
}

const std::unordered_map<std::string,bool> Bindings::getCommandMapFromKeycodes(const std::unordered_map<std::string,bool> &keycodes){
    std::unordered_map<std::string, bool> command_map;
    std::string keycode;
    std::string command;
    for (auto pair:keycodes){
        keycode=pair.first;
        command = getCommand(keycode);
        if (command !="NA") { command_map.insert_or_assign(command,true); }
    }
    return command_map;
}

void Bindings::bindKeyValuePair(std::string input_string){
	input_string.erase(std::remove_if(input_string.begin(), input_string.end(), ::isspace), input_string.end());
	std::pair<std::string,Uint32> key_value_pair;
	std::stringstream s_stream(input_string); //create string stream from the string
	
    std::string this_command, this_device, this_keycode;
	getline(s_stream, this_command, '='); //get first string delimited by comma
    getline(s_stream, this_device, ':');
    getline(s_stream, this_keycode, ';');
    

    //Uint32 this_int_value = static_cast<Uint32>(std::stoul(this_keycode));
    bindings.insert_or_assign(this_device+":"+this_keycode, this_command);
} 

void Bindings::loadBinding(std::string filename){
    std::ifstream myfile;
	//filename = "Meshes/"+filename;
	std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
	myfile.open (filename);
    if (!myfile)
    throw std::runtime_error(std::string("Bindings::loadBinding - Could not open file: ")+filename);


	if (myfile.is_open()) {
        std::cout<<"File Open " << std::endl;
        std::string line;
        std::string comment = "#";
        char linefeed = '\n';
        int tri_id=0;
        while (std::getline(myfile, line)) {

            if (line.substr(0,1)!= comment) {
                // Line is not a comment
                if (line.back()!=linefeed && line.back()==';'){
                    // Line is a properly formatted, terminating with a ;
                    std::cout << line << std::endl;
                    bindKeyValuePair(line);

                }else if (line.empty()){
                    // Empty line, do nothing
                }else{
                    std::cout<< "Bad line! -> " << line << std::endl;
                }

            }
            
        }
    myfile.close();
    }
}

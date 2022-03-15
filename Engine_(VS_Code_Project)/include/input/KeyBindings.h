#ifndef KEYBINDINGS_H
#define KEYBINDINGS_H
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>


/**
 * @brief This class helps load keycode:action bindings from a file, stores the bindings as an unordered map, and translates a map of keycodes to a map of mapped commands that the engine will recognize.
 * 
 */
class Bindings{
    public:
    /**
     * @brief Loads key binding information from a file.  
     * 
     * @param filename this is a string representation of the filename such as "config.cfg".  Each line of the file is formatted with a key value pair.  The pair is separated by an "=" and each line must end with a ";".  An example is as follows:
     * <command> = <number>;
     * WALK_FORWARD = 119;
     * WALK_BACKWARD = 115;
     * ...
     * QUIT = 27;
     * 
     * <command> is a string such as MOVE_FORWARD, or MOVE_BACKWARD
     * <number> is a Uint32 reprentation of the SDLK_ enumerated keycodes such as SDKL_w, SDLK_s
     */
    void loadBinding(std::string filename);


    /**
     * @brief This method adds a std:string based command to the bindings map.
     * 
     * @param input_string 
     */
    void bindKeyValuePair(std::string input_string);
        
    /**
     * @brief Given a map of keycodes, this method returns a new map with the corresponding commands form the binding.  If a key code is listed that isn't contained in the bindings, the method will return "NA" for that command.  The engine drop "NA" commands when adding commands to the active command vector. 
     * 
     * @param keycodes 
     * @return const std::unordered_map<std::string,bool> 
     */
    const std::unordered_map<std::string,bool> getCommandMapFromKeycodes(const std::unordered_map<std::string,bool> &keycodes);

    private: 
    std::unordered_map<std::string, std::string> bindings;   
    std::string getCommand(std::string key_code); 

};


#endif
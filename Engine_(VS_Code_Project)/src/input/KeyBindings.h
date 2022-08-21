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

    /**
     * @brief this is a command map formatted with a string:string pair as follows:
     * std::string(<Device>:<Scancode>) , std::string(<Command Name>)
     * Why is the scancode a string and now a Uint64?  Because the mouse and Keyboard both have a scancode "1" with different inputs
     * 
     */
    std::unordered_map<std::string, std::string> bindings;   
    
    
    /**
     * @brief Given the std::string key_code, this function will return the corresponding std::string command
     * 
     * @param key_code 
     * @return std::string 
     */
    std::string getCommand(std::string key_code); 

};


#endif
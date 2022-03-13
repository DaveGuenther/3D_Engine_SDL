#ifndef RAW_INPUT_H
#define RAW_INPUT_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>

class Raw_Input{
    public:
    virtual void getInput(std::vector<bool, int>& input_map)=0;

};

class KeyboardInput: public Raw_Input{
    public:
    virtual void getInput(std::vector<bool, int>& input_map){
    

    }
};

#endif
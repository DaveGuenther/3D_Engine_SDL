#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include "../objects/OBJ_Lex_textureCoord.h"

void OBJ_Lex_textureCoord::lex(std::string thisLine){
    std::vector<std::string> tokens;
    std::stringstream check1(thisLine);
    std::string intermediate;
    
    // Locate next space and add token to characters before space
    while(std::getline(check1, intermediate, ' ')){
        tokens.push_back(intermediate);
    }

    // assign tokens to private structure up to 3 elements
    if (tokens.size()>=2){
        this->u = std::stof(tokens[0]);
        this->v = std::stof(tokens[1]);

    }

    // assign 4th element if it exists
    if (tokens.size()==3){
        this->w = std::stof(tokens[3]);
    }
    
}


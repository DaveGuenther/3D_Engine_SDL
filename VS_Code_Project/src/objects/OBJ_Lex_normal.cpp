#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include "OBJ_Lex_normal.h"


void OBJ_Lex_normal::lex(std::string thisLine){
    std::vector<std::string> tokens;
    std::stringstream check1(thisLine);
    std::string intermediate;
    
    // Locate next space and add token to characters before space
    while(std::getline(check1, intermediate, ' ')){
        tokens.push_back(intermediate);
    }

    // assign tokens to private structure up to 3 elements
    if (tokens.size()>=3){
        this->thisNormal.x=std::stof(tokens[0]);
        this->thisNormal.y=std::stof(tokens[1]);
        this->thisNormal.z=std::stof(tokens[2]);

    }

    
}

Vec3d OBJ_Lex_normal::getNormal(){
    return this->thisNormal;
}


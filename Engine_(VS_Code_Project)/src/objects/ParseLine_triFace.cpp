#include "objects/ParseLine_triFace.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

void ParseLine_triFace::parse(std::string thisLine){
    std::vector<std::string> tokens;
    std::stringstream check1(thisLine);
    std::string intermediate;
    
    // Locate next space and add token to characters before space
    while(std::getline(check1, intermediate, ' ')){
        tokens.push_back(intermediate);

    }

    for (auto token:tokens){
        std::stringstream this_stream(token);
        std::string token_b, token_c, token_a;
        std::getline(this_stream,token_a,'/');
        std::getline(this_stream,token_b,'/');
        std::getline(this_stream,token_c);

        vertex_ids.push_back(std::stoi(token_a));
        texture_coord_ids.push_back(std::stoi(token_b));
        normal_ids.push_back(std::stoi(token_c));

    }

}

std::vector<int> ParseLine_triFace::getVertexIDs(){
    return this->vertex_ids;
}


std::vector<int> ParseLine_triFace::getTextureCoords(){
    return this->texture_coord_ids;
}

std::vector<int> ParseLine_triFace::getNormalIDs(){
    return this->normal_ids;
}
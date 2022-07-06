#include <string>
#include <fstream>
#include <filesystem>
#include "objects/MTL.h"

MTL::MTL(std::string filename){
    filename = "Meshes/"+filename;
	//std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
	myMTLfile.open (filename);
    if (!myMTLfile)
        throw std::runtime_error(std::string("MTL::MTL - Could not open file: ")+filename);



}

bool MTL::peekline( std::ifstream & is, std::string & s ){
    std::streampos sp = is.tellg();
    if(getline( is, s )){
        std::streampos sp2 = is.tellg();
        is.seekg( sp );
        sp = is.tellg();
        return true;
    }else{
        s = "EOF";
        return false;
    }
    
}

void MTL::parseMTL(){

}
#include "objects/OBJ_Parse.h"

#include <string>
#include <iostream>

int main(int argv, char** args)
{
    std::string filename = "cube.obj";
    OBJ_Parse thisOBJ(filename);
    
    std::cout << "hello" << std::endl;
	return 0;
}   
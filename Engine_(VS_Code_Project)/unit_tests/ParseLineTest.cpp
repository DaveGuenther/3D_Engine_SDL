#include "objects/ParseLine_vertex.h"
#include "objects/ParseLine_textureCoord.h"
#include "objects/ParseLine_normal.h"
#include "objects/ParseLine_triFace.h"
#include <string>
#include <iostream>

int main(int argv, char** args)
{
    /////  Text Vertex Read Line  /////
    std::string myvertstring = "v 1.000000 2.017787 -1.000000";
    char space = ' ';

    // Get the position of first occurrence of character
    std::size_t pos = myvertstring.find(space);


    // Check if index position is valid  
    if (pos != std::string::npos)
    {
        // Remove all characters before the given position 
        myvertstring = myvertstring.substr(pos+1);
    }

	
    ParseLine_vertex thisLine;
    thisLine.parse(myvertstring);

    std::cout << "Vertex" << std::endl;
    std::cout << thisLine.getX() << std::endl;
    std::cout << thisLine.getY() << std::endl;
    std::cout << thisLine.getZ() << std::endl;
    std::cout << thisLine.getW() << std::endl;

    /////  Text Texture Coordinate Read Line  /////
    std::string mytextstring = "vt 0.875000 0.500000";
   
    // Get the position of first occurrence of character
    pos = mytextstring.find(space);


    // Check if index position is valid  
    if (pos != std::string::npos)
    {
        // Remove all characters before the given position 
        mytextstring = mytextstring.substr(pos+1);
    }

	
    ParseLine_textureCoord textureLine;
    textureLine.parse(mytextstring);

    std::cout << "Texture Coordinate" << std::endl;
    std::cout << textureLine.getU() << std::endl;
    std::cout << textureLine.getV() << std::endl;
    std::cout << textureLine.getW() << std::endl;


    /////  Text Normal Read Line  /////
    std::string mynormalstring = "vn 0.0000 1.0000 0.0000";
   
    // Get the position of first occurrence of character
    pos = mynormalstring.find(space);


    // Check if index position is valid  
    if (pos != std::string::npos)
    {
        // Remove all characters before the given position 
        mynormalstring = mynormalstring.substr(pos+1);
    }

	
    ParseLine_normal normalLine;
    normalLine.parse(mynormalstring);

    std::cout << "Texture Coordinate" << std::endl;
    std::cout << normalLine.getNormal().toString() << std::endl;
   

   ///////  Triangle Face Read Line  //////
     std::string mytristring = "f 5/1/1 3/2/1 1/3/1";
   
    // Get the position of first occurrence of character
    pos = mytristring.find(space);


    // Check if index position is valid  
    if (pos != std::string::npos)
    {
        // Remove all characters before the given position 
        mytristring = mytristring.substr(pos+1);
    }

	
    ParseLine_triFace triLine;
    triLine.parse(mytristring);
    std::vector<int> verts, texts, norms;
    verts = triLine.getVertexIDs();
    texts = triLine.getTextureCoords();
    norms = triLine.getNormalIDs();
    std::cout << "triangle Face definitions" << std::endl;
    for (int i=0;i<3;i++){
        std::cout << verts[i] << "/" << texts[i] << "/" << norms[i] << std::endl;
    }
	return 0;
}   
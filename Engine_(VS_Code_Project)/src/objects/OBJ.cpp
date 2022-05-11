#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <iostream>

#include "objects/OBJ_Parse.h"
#include "objects/OBJ.h"
#include "utility/Mesh.h"
#include "utility/Triangle.h"

bool OBJ::peekline( std::ifstream & is, std::string & s ){
    std::streampos sp = is.tellg();
    if(getline( is, s )){
        is.seekg( sp );
        return true;
    }else{
        s = "EOF";
        return false;
    }
    
}

OBJ::OBJ(std::string filename){

    std::ifstream myfile;
	filename = "Meshes/"+filename;
	std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
	myfile.open (filename);
    

    /*//park all tis into a struct above obj class, then make a private vector of structs in obj to expost to the pipeline
    std::vector<std::stringstream> meshblocks;  // each stringstream will be a meshblock from the file delimited by lines that start with "o"
    std::vector<std::string> mesh_name;
    //std::vector<std::vector<std::string>> mtl;  */

    bool notEOF=true;
    std::string line, nextToken, mtlfile;
	if (myfile.is_open()) {   
        
        // Start getting tokens until first "o" comes up
        std::stringstream meshStream; 
        std::string name;
        std::string this_usemtl;
        std::string nextToken="#";
        while(nextToken!="o"){
            
            // getline and extract token
            std::getline(myfile, line);
            std::stringstream this_stream(line);
            std::string keyword, lexLine;   
            std::getline(this_stream,keyword,' ');
            std::getline(this_stream,lexLine);
            
            // parse "mtllib" lines
            if (keyword=="mtllib"){ // mtllib line
                //record mtllib information for this mesh
                mtlfile = lexLine;
            }         

            notEOF = peekline(myfile, line);
            // get nextToken
            this_stream.clear();
            this_stream << line;
            std::getline(this_stream,nextToken,' ');
            
        }    
        std::getline(myfile, line); // this is an "o" line
        std::stringstream this_stream(line);
        std::string keyword, lexLine;   
        std::getline(this_stream,keyword,' ');
        std::getline(this_stream,lexLine);
        name=lexLine;
        this_stream.clear();
        //while (notEOF)
        while(notEOF){
            //getline
            std::getline(myfile, line); // this is an "o" line
            
            //add line to stringstream
            meshStream << line;
            
            //notEOF= peekahead
            notEOF = peekline(myfile, line);
            // get nextToken
            this_stream.clear();
            meshStream << line;
            std::getline(this_stream,nextToken,' ');


            //if nextToken == "usemtl"
            if (keyword=="usemtl"){ // capture material used
                // get this mtl line and store it
                std::getline(myfile, line); // this is an "o" line
                this_stream.clear();
                this_stream << line;
                std::getline(this_stream,keyword,' ');
                std::getline(this_stream,lexLine);
                
                // Assign material
                this_usemtl = lexLine;
            }   

            //if nextToken == "o"
            if (keyword=="o"){ // new mesh object line
                //build raw Datum object and push Datum to OBJ_Data
                OBJ_Datum this_datum;
                this_datum.mesh_name=name;
                meshStream << this_datum.meshblocks.rdbuf();
                this_datum.mtl = this_usemtl;
                this->OBJ_Data.push_back(this_datum);
                
                //clear stringstream
                meshStream.clear();
            }            

        }
        
        OBJ_Datum this_datum;
        this_datum.mesh_name=name;
        meshStream << this_datum.meshblocks.rdbuf();
        this_datum.mtl=this_usemtl;
        this->OBJ_Data.push_back(this_datum);
        //push stringstream to vector
    

        
        
    /*OBJ_Parse this_OBJ(filename);
    Mesh thisMesh(0);
    int tri_id=0;
    for (auto triangle: this_OBJ.triangleFaces){
        Triangle thisTri;
        std::vector<int> vertIDs = triangle.vertex_ids;
        for (int i=0;i<3;i++){
            int vertex_ID = vertIDs[i]-1;
            Vec3d this_vert = Vec3d(this_OBJ.vertices[vertex_ID].x,
                                    this_OBJ.vertices[vertex_ID].y,
                                    this_OBJ.vertices[vertex_ID].z);
            thisTri.setTrianglePoint(i,this_vert);
            
        }
        thisTri.setID(tri_id);
        thisMesh.add3dTriangle(thisTri);
        tri_id+=1;
        
    }
    this->thisMesh=thisMesh;*/
    }
}

std::vector<Mesh>& OBJ::getMeshes(){
    return this->Meshes;
}
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

void OBJ::split_OBJ_Chunks(){
    std::vector<std::vector<std::string>> mesh_streams;
    
    
    
    
    //std::vector<OBJ_Datum> myOBJ_Data;

    bool notEOF=true;
    std::string line, nextToken, mtlfile;
	if (myfile.is_open()) {   
        
        // Start getting tokens until first "o" comes up
        std::stringstream meshStream; 
        std::string name;
        std::string this_usemtl;
        std::string nextToken="#";
        while(nextToken!="o"){ 
            // This while loop is really just looking for the mtllib token in the obj file before 
            // the first "o" object definition
            
            // getline and extract token
            std::getline(myfile, line);
            std::stringstream this_stream(line);
            std::string keyword, lexLine, str_this_stream;   
            std::getline(this_stream,keyword,' ');
            std::getline(this_stream,lexLine);
            str_this_stream = this_stream.str();
            
            // parse "mtllib" lines
            if (keyword=="mtllib"){ // mtllib line
                //record mtllib information for this mesh
                mtlfile = lexLine;
            }         

            notEOF = peekline(myfile, line);
            // get nextToken
            std::stringstream this_peek_stream(line);
            this_peek_stream << line << std::endl;

            str_this_stream = this_peek_stream.str();
            std::getline (this_peek_stream,nextToken,' '); 
            
        }   

        // This block works through the first "o" line 
        std::getline(myfile, line); // this is an "o" line
        std::stringstream o_token_stream(line);
        
        std::string keyword, lexLine, str_this_stream; 
        str_this_stream = o_token_stream.str();  
        std::getline(o_token_stream,keyword,' ');
        std::getline(o_token_stream,lexLine);
        name=lexLine; // this is the value after the "o" token
        
        std::stringstream this_stream;

        std::vector<std::string> this_mesh_block;

        //while (notEOF) go through the rest of the file breaking objects out into their own 
        while(notEOF){
            
            //getline
            std::getline(myfile, line); 
            
            //add line to stringstream
            this_mesh_block.push_back(line);


            //notEOF= peekahead
            notEOF = peekline(myfile, line);
            // get nextToken
            std::stringstream this_peek_stream(line);
            std::getline(this_peek_stream,nextToken,' ');


            
            if (nextToken=="usemtl"){ // capture material used
                // get this mtl line and store it
                std::getline(myfile, line); // this is an "o" line
                
                this_mesh_block.push_back(line);
                
                std::stringstream temp_str_stream(line);
                str_this_stream = temp_str_stream.str(); 
                std::getline(temp_str_stream,keyword,' ');
                std::getline(temp_str_stream,lexLine);
                
                // Assign material
                this_usemtl = lexLine;
            }   

            //if nextToken == "o"
            if (nextToken=="o"){ // new mesh object line

                OBJ_Datum this_datum("");
                for (std::string temp_line: this_mesh_block){
                    (*this_datum.meshblocks) << temp_line << std::endl;
                }
                this_datum.mesh_name=name;
                this_datum.mtl = this_usemtl;
                this_datum.this_mesh_block = this_mesh_block;
                this_mesh_block.clear();
                myOBJ_Data.push_back(this_datum);
                
                //clear stringstream
                this_stream.clear();
            }            

        }

        std::string mesh_stream_string = this_stream.str();
        OBJ_Datum this_datum("");
        for (std::string temp_line: this_mesh_block){
            (*this_datum.meshblocks) << temp_line << std::endl;
        }

        this_datum.mesh_name=name;
        this_datum.this_mesh_block = this_mesh_block;
        this_datum.mtl=this_usemtl;
        myOBJ_Data.push_back(this_datum);
        //push stringstream to vector
        mesh_streams.push_back(this_mesh_block);

    }

}

OBJ::OBJ(std::string filename){

    filename = "Meshes/"+filename;
	std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
	myfile.open (filename);

    //std::ifstream myfile;
    split_OBJ_Chunks();
    

    /*//park all tis into a struct above obj class, then make a private vector of structs in obj to expost to the pipeline
    std::vector<std::stringstream> meshblocks;  // each stringstream will be a meshblock from the file delimited by lines that start with "o"
    std::vector<std::string> mesh_name;
    //std::vector<std::vector<std::string>> mtl;  */
/*
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
                //OBJ_Datum this_datum;
                //this_datum.mesh_name=name;
                //meshStream << this_datum.meshblocks.rdbuf();
                //this_datum.mtl = this_usemtl;
                //this->OBJ_Data.push_back(this_datum);
                
                //clear stringstream
                meshStream.clear();
            }            

        }
        
        //OBJ_Datum this_datum;
        //this_datum.mesh_name=name;
        //meshStream << this_datum.meshblocks.rdbuf();
        //this_datum.mtl=this_usemtl;
        //this->OBJ_Data.push_back(this_datum);
        //push stringstream to vector
    
*/
        
    for (auto this_chunk:this->myOBJ_Data){
        OBJ_Parse this_OBJ((*this_chunk.meshblocks));
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
            
            /* Eventually place the information on texture coords here

            */

            thisTri.setID(tri_id);
            thisMesh.add3dTriangle(thisTri);
            tri_id+=1;
            
        }
        this->Meshes.push_back(thisMesh);  
    }    
    
}


std::vector<Mesh>& OBJ::getMeshes(){
    return this->Meshes;
}
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "objects/OBJ_Chunk.h"
#include "objects/OBJ.h"
#include "objects/MTL.h"
#include "utility/Mesh.h"
#include "utility/Triangle.h"

OBJ::OBJ(std::string filename, std::shared_ptr<TextureList> texture_list){

    this->forceClockwiseWinding=true;
    this->flip_X_Coords=true;
    buildMesh(filename); 
    std::string toErase = ".obj";
    this->filename = filename.erase(filename.find(toErase),toErase.length());
   
}

OBJ::OBJ(std::string filename, bool forceClockwiseWinding, bool flip_X_Coords){

    this->forceClockwiseWinding=forceClockwiseWinding;
    this->flip_X_Coords=flip_X_Coords;
    buildMesh(filename); 
    
}

bool OBJ::peekline( std::ifstream & is, std::string & s ){
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

void OBJ::split_OBJ_Chunks(){
    std::vector<std::vector<std::string>> mesh_streams;

    bool notEOF=true;
    std::string line, nextToken, mtlfile;
	if (myfile.is_open()) {   
        
        // Start getting tokens until first "o" comes up
        std::stringstream meshStream; 
        std::string name;
        std::string this_usemtl;
        std::string nextToken="#";
        std::streampos sp;
        while(nextToken!="o"){ 
            // This while loop is really just looking for the mtllib token in the obj file before 
            // the first "o" object definition
            
            // getline and extract token
            sp = myfile.tellg();
            std::getline(myfile, line);
            sp = myfile.tellg();
            std::stringstream this_stream(line);
            std::string keyword, lexLine, str_this_stream;   
            std::getline(this_stream,keyword,' ');
            std::getline(this_stream,lexLine);
            str_this_stream = this_stream.str();
            sp = myfile.tellg();
            // parse "mtllib" lines
            if (keyword=="mtllib"){ // mtllib line
                //record mtllib information for this mesh
                mtlfile = lexLine;
                
            }         

            notEOF = peekline(myfile, line);
            sp = myfile.tellg();
            // get nextToken
            std::stringstream this_peek_stream(line);
            this_peek_stream << line << std::endl;
            sp = myfile.tellg();
            str_this_stream = this_peek_stream.str();
            std::getline (this_peek_stream,nextToken,' '); 
            sp = myfile.tellg();
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
                this_datum.material.push_back(this_usemtl);
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
        this_datum.material.push_back(this_usemtl);
        myOBJ_Data.push_back(this_datum);
        //push stringstream to vector
        mesh_streams.push_back(this_mesh_block);

    }

}



void OBJ::assembleChunks(){
    this->totalTextureCoords=0;
    this->totalVertices=0;
    int X_CoordinateInverter=1;
    if (this->flip_X_Coords==true){ X_CoordinateInverter=-1; } 
    for (auto this_chunk:this->myOBJ_Data){
        OBJ_Chunk this_OBJ_Chunk((*this_chunk.meshblocks));

        Mesh thisMesh(0);
        int tri_id=0;
        for (auto triangle: this_OBJ_Chunk.triangleFaces){
            Triangle thisTri;
            std::vector<int> vertIDs = triangle.vertex_ids;
            for (int i=0;i<3;i++){
                int normal_offset_id = i;
                if (this->forceClockwiseWinding==true){
                    if (i==0){
                    normal_offset_id=2;
                    }
                    if (i==2){
                        normal_offset_id=0;
                    }
                }
                int vertex_ID = vertIDs[normal_offset_id]-1-this->totalVertices;
                Vec3d this_vert = Vec3d(this_OBJ_Chunk.vertices[vertex_ID].x*X_CoordinateInverter,
                                        this_OBJ_Chunk.vertices[vertex_ID].y,
                                        this_OBJ_Chunk.vertices[vertex_ID].z);
                thisTri.setTrianglePoint(i,this_vert);
                
            }
            
            /* Eventually place the information on texture coords here
            
            */
           std::vector<int> texIDs = triangle.texture_coord_ids;
           for (int i=0;i<3;i++){
                int normal_offset_id = i;
                if (this->forceClockwiseWinding==true){
                    if (i==0){
                    normal_offset_id=2;
                    }
                    if (i==2){
                        normal_offset_id=0;
                    }
                }
                int tex_ID = texIDs[normal_offset_id]-1-this->totalTextureCoords;
                Vec3d this_tex_coord = Vec3d(this_OBJ_Chunk.textureCoords[tex_ID].u,
                                        this_OBJ_Chunk.textureCoords[tex_ID].v,
                                        this_OBJ_Chunk.textureCoords[tex_ID].w);
                thisTri.setTriangleTexturePoint(i,this_tex_coord);
                
            }
           //int tex_ID = vertIDs[normal_offset_id]-1-this->totalVertices;
            
            thisTri.setID(tri_id);
            thisMesh.add3dTriangle(thisTri);
            tri_id+=1;

            
        }
        this->totalTextureCoords+=this_OBJ_Chunk.getTotalTextCoordNum();
        this->totalVertices+=this_OBJ_Chunk.getTotalVertexNum();
        this->Meshes.push_back(thisMesh);  
    }   
}

void OBJ::buildMesh(std::string filename){
    filename = "Meshes/"+filename;
	std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
	myfile.open (filename);
    if (!myfile)
        throw std::runtime_error(std::string("OBJ::buildMesh - Could not open file: ")+filename);

    //std::ifstream myfile;
    split_OBJ_Chunks();
    assembleChunks();
    
}

std::vector<Mesh>& OBJ::getMeshes(){
    return this->Meshes;
}
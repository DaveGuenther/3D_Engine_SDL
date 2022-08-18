#include <string>
#include <fstream>
//#include <ifstream>
#include <filesystem>
#include <unordered_map>
#include "../materials/MTL.h"

MTL::MTL(std::string filename){
    filename = "Meshes/"+filename;
	//std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
	myMTLfile.open (filename);
    if (!myMTLfile)
        throw std::runtime_error(std::string("MTL::MTL - Could not open file: ")+filename);
    parseMTL();
}

const std::unordered_map<std::string, std::string>& MTL::getMTL_map(){
    return this->materials;
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
    

    bool notEOF=true;
    std::string line, nextToken, mtlfile;
	if (myMTLfile.is_open()) {   
        
        // Start getting tokens until first "o" comes up
        std::stringstream meshStream; 
        std::string name;
        std::string this_usemtl;
        std::string nextToken="#";
        std::streampos sp;
        while(nextToken!="newmtl" && notEOF){ 
            // This while loop is really just looking for the mtllib token in the obj file before 
            // the first "newmtl" object definition
            
            // getline and extract token
            sp = myMTLfile.tellg();
            std::getline(myMTLfile, line);
            sp = myMTLfile.tellg();
            std::stringstream this_stream(line);
            std::string keyword, lexLine, str_this_stream;   
            std::getline(this_stream,keyword,' ');
            std::getline(this_stream,lexLine);
            str_this_stream = this_stream.str();
            sp = myMTLfile.tellg();

            notEOF = peekline(myMTLfile, line);
            sp = myMTLfile.tellg();
            // get nextToken
            std::stringstream this_peek_stream(line);
            this_peek_stream << line << std::endl;
            sp = myMTLfile.tellg();
            str_this_stream = this_peek_stream.str();
            std::getline (this_peek_stream,nextToken,' '); 
            sp = myMTLfile.tellg();
        }   

        if(notEOF){
            // This block works through the first "newmtl" line 
            std::getline(myMTLfile, line); // this is an "newmtl" line
            std::stringstream newmtl_token_stream(line);
            
            std::string keyword, lexLine, str_this_stream; 
            str_this_stream = newmtl_token_stream.str();  
            std::getline(newmtl_token_stream,keyword,' ');
            std::getline(newmtl_token_stream,lexLine);
            name=lexLine; // this is the value after the "newmtl" token.  Save for later
            
            std::stringstream this_stream;

            //std::vector<std::string> this_mesh_block;

            //while (notEOF) go through the rest of the file breaking objects out into their own 
            while(notEOF){
                
                //getline
                std::getline(myMTLfile, line); 
                
                //add line to stringstream
                //this_mesh_block.push_back(line);


                //notEOF= peekahead
                notEOF = peekline(myMTLfile, line);
                // get nextToken
                std::stringstream this_peek_stream(line);
                std::getline(this_peek_stream,nextToken,' ');


                
                if (nextToken=="map_Kd"){ // capture material used
                    // get this mtl line and store it
                    std::getline(myMTLfile, line); // this is a "newmtl" line
                    
                    //this_mesh_block.push_back(line);
                    
                    std::stringstream temp_str_stream(line);
                    str_this_stream = temp_str_stream.str(); 
                    std::getline(temp_str_stream,keyword,' ');
                    std::getline(temp_str_stream,lexLine);
                    
                    // Assign material
                    this->materials.insert_or_assign(name,lexLine);
                }   

                //if nextToken == "newmtl"
                if (nextToken=="newmtl"){ // new mesh object line

                    std::getline(myMTLfile, line); // this is an "newmtl" line
                    std::stringstream newmtl_token_stream2(line);
                    
                    //std::string str_this_stream; 
                    str_this_stream = newmtl_token_stream2.str();  
                    std::getline(newmtl_token_stream2,keyword,' ');
                    std::getline(newmtl_token_stream2,lexLine);
                    name=lexLine; // this is the value after the "newmtl" token.  Save for later
                    
                    
                    
                    //clear stringstream
                    this_stream.clear();
                }            

            }
        }
    }
}
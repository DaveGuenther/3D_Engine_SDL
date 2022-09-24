#include <string>
#include <sstream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <iostream>

class OBJ_Datum{
    public:
    OBJ_Datum(std::string raw_mesh_data):meshblocks(new std::stringstream(raw_mesh_data)){ }
    std::stringstream* meshblocks;
    std::vector<std::string> this_mesh_block;
    std::string mesh_name; // each mesh gets a name
    std::string mtl; // 
};

bool peekline( std::ifstream & is, std::string & s ){
    std::streampos sp = is.tellg();
    if(getline( is, s )){
        is.seekg( sp );
        return true;
    }else{
        s = "EOF";
        return false;
    }
    
}

int main(int argv, char** args)
{
    std::vector<std::vector<std::string>> mesh_streams;
    
    std::string filename = "Compass.obj";

    std::ifstream myfile;
	filename = "Meshes/"+filename;
	std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
	myfile.open (filename);
    
    std::vector<OBJ_Datum> myOBJ_Data;

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

    std::cout << "hello" << std::endl;
	return 0;
}   
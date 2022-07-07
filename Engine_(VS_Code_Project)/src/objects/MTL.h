#ifndef MTL_H
#define MTL_H
#include <unordered_map>

class MTL{
    public:
        MTL(std::string filename);

        
    private:

        void parseMTL();

        /**
         * @brief This private function is used internally.  It offers the ability to "peek ahead" in an std:ifstream and return
         * the nect token in a stream and then replace the cursor back at it's original place in the stream.  We use this to look ahead for 
         * end of file scenarios
         * 
         * @param is This is a reference to the ifstream
         * @param s this is the next token captured in the ifstream
         * @return true if there are still more tokens in the file
         * @return false if the next token results in an EOY scenario
         */
        bool peekline( std::ifstream & is, std::string & s );
        
        std::ifstream myMTLfile;
        std::unordered_map<std::string,std::string> materials;  // (material name, file name)

};

#endif
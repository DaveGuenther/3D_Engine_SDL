#ifndef LEXLINE_TRIFACE_H
#define LEXLINE_TRIFACE_H

#include <string>
#include <vector>

class OBJ_Lex_triFace{

    public:
        void lex(std::string thisLine);
        std::vector<int> vertex_ids;
        std::vector<int> texture_coord_ids;
        std::vector<int> normal_ids;

};


#endif
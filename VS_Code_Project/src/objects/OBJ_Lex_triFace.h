#ifndef LEXLINE_TRIFACE_H
#define LEXLINE_TRIFACE_H

#include <string>
#include <vector>

/**
 * @brief TThis class will lex the tokens for a single line if the line starts with "f" indicating it is a triangleFace defininition
 */
class OBJ_Lex_triFace{

    public:
        void lex(std::string thisLine);
        std::vector<int> vertex_ids;
        std::vector<int> texture_coord_ids;
        std::vector<int> normal_ids;
        std::string texturefile;

};


#endif




#ifndef LEXLINE_TRIFACE_H
#define LEXLINE_TRIFACE_H

#include <string>
#include <vector>

class LexLine_triFace{
    private:
        std::vector<int> vertex_ids;
        std::vector<int> texture_coord_ids;
        std::vector<int> normal_ids;

    public:
        void lex(std::string thisLine);
        std::vector<int> getVertexIDs();
        std::vector<int> getTextureCoords();
        std::vector<int> getNormalIDs();

};


#endif
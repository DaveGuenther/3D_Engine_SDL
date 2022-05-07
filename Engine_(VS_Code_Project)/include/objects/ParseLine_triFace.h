#ifndef PARSELINE_TRIFACE_H
#define PARSELINE_TRIFACE_H

#include <string>
#include <vector>

class ParseLine_triFace{
    private:
        std::vector<int> vertex_ids;
        std::vector<int> texture_coord_ids;
        std::vector<int> normal_ids;

    public:
        void parse(std::string thisLine);
        std::vector<int> getVertexIDs();
        std::vector<int> getTextureCoords();
        std::vector<int> getNormalIDs();

};


#endif
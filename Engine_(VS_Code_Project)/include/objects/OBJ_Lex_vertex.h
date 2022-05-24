#ifndef LEXLINE_VERTEX_H
#define LEXLINE_VERTEX_H

#include <string>

class OBJ_Lex_vertex{
    public:
        OBJ_Lex_vertex();
        void lex(std::string thisLine);

        float x;
        float y;
        float z;
        float w = 1.0f;

    private:

};

#endif
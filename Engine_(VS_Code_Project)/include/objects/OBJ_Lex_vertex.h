#ifndef LEXLINE_VERTEX_H
#define LEXLINE_VERTEX_H

#include <string>

/**
 * @brief This class will lex the tokens for a single line if the line starts with "v" indicating it is a vertex vetor
 */
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
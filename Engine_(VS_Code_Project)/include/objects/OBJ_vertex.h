#ifndef LEXLINE_VERTEX_H
#define LEXLINE_VERTEX_H

#include <string>

/*class OBJ_triFace:public ILexLine{
    private:
        struct face{
            int vertex_id;
            int text_coord_id;
            int normal_id;
        };

    public:
        void lex(std::string thisLine);
        face& getFace();
};

class OBJ_normal:public ILexLine{
    private:
        struct normal{
            float x;
            float y;
            float z;
        };
    
    public:
        void lex(std::string thisLine);
        normal& getNormal();
};

class OBJ_texture_coord:public ILexLine{
    private:
        struct textureCoord{
            float u;
            float v=0.0f;
            float w=0.0f;
        };

    public:
        void lex(std::string thisLine);
        textureCoord& getTextureCoord();
};*/

class OBJ_vertex{
    public:
        OBJ_vertex();
        void lex(std::string thisLine);
        float getX();
        float getY();
        float getZ();
        float getW();

        float x;
        float y;
        float z;
        float w = 1.0f;

    private:

};

#endif
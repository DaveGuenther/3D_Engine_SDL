#ifndef PARSELINE_VERTEX_H
#define PARSELINE_VERTEX_H

#include <string>

/*class ParseLine_triFace:public IParseLine{
    private:
        struct face{
            int vertex_id;
            int text_coord_id;
            int normal_id;
        };

    public:
        void parse(std::string thisLine);
        face& getFace();
};

class ParseLine_normal:public IParseLine{
    private:
        struct normal{
            float x;
            float y;
            float z;
        };
    
    public:
        void parse(std::string thisLine);
        normal& getNormal();
};

class ParseLine_texture_coord:public IParseLine{
    private:
        struct textureCoord{
            float u;
            float v=0.0f;
            float w=0.0f;
        };

    public:
        void parse(std::string thisLine);
        textureCoord& getTextureCoord();
};*/

class ParseLine_vertex{
    public:
        ParseLine_vertex();
        void parse(std::string thisLine);
        float getX();
        float getY();
        float getZ();
        float getW();

    private:
        float x;
        float y;
        float z;
        float w = 1.0f;
};

#endif
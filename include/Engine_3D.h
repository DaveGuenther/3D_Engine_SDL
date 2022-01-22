#ifndef ENGINE_3D_H
#define ENGINE_3D_H
#include "Renderer.h"

class Engine_3D{
    private:
        Renderer Engine_Renderer;
        bool isRunning;
        SDL_Event event;
        std::vector<Mesh> mesh_pipeline;
    public:
        Engine_3D(void);
        void load_meshes();
        bool is_running();
        void engine_update();
        void shutdown();

};

#endif
#ifndef ENGINE_3D_H
#define ENGINE_3D_H
#include "Renderer.h"
#include "Mesh_Pipeline.h"
#include "Triangle_Modifications_Pipeline.h"

/**
 * @brief This is the base class of the 3D engine.  It initializes the other key systems like Renderer and Input classes.  It manages updates of the various subsystems.
 * 
 */
class Engine_3D{
    private:
        Renderer Engine_Renderer;
        bool isRunning; //If set to false, this will end the 3D engine during the next engine_update()
        SDL_Event event;
        Mesh_Pipeline mesh_pipeline; // contains all of the objects that the engine will need to render
        //Triangle_Modifications_Pipeline tri_modifications;
        float fTheta, tTheta;
        std::vector<Triangle_Modifier*> modifications;
        
    public:
        Engine_3D(void);
        /**
         * @brief This method will load a file housing informations about mesh objects to load and then invoke the Mesh_Pipeline.Add_Mesh_to_Pipeline() method
         * 
         */
        void load_meshes();
        /**
         * @brief This Getter method tells the main game loop the status of the engine, it should be used to terminate the game loop in main()
         * 
         */
        bool is_running();
        /**
         * @brief This method is called once during the game loop.  It queries for input, requests mesh rotations and translations, and projects the new frame on the screen.
         * 
         */
        void engine_update();
        /**
         * @brief Used to shutdown the SDL systems.
         * 
         */
        void shutdown();

};

#endif
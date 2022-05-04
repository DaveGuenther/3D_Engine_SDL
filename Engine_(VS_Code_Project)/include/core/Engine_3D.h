#ifndef ENGINE_3D_H
#define ENGINE_3D_H

#include <memory>

#include "core/GameState_Observer_Pattern.h"
#include "core/Frame_Rate_Manager.h"
#include "input/Input_Parser.h"
#include "actions/Action_Updater.h"
#include "utility/Mesh_Pipeline.h"
#include "render/Renderer.h"
#include "render/Camera.h"

/**
 * @brief This is the base class of the 3D engine.  It initializes the other key systems like Renderer and Input classes.  It manages updates of the various subsystems.
 * 
 */
class Engine_3D{
    private:

        
        std::shared_ptr<Renderer> Engine_Renderer;
        

        bool isRunning; //If set to false, this will end the 3D engine during the next engine_update()
        
        std::shared_ptr<Mesh_Pipeline> mesh_pipeline;
        //Mesh_Pipeline* mesh_pipeline; // contains all of the objects that the engine will need to render
     


        //Triangle_Modifications_Pipeline tri_modifications;
        
        GameStateSubject game_state_subject;
        std::shared_ptr<Game_Engine_State_Observer> Engine_State;
        //Game_Engine_State_Observer* Engine_State;
        float fTheta, tTheta;
        Input_Parser* MENU_Input_Parser;
        Input_Parser* INWORLD_Input_Parser; 

        InGame_Action_Updater* INWORLD_Action_Updater;

        float FPS;
        Frame_Rate_Manager* VariableFrameRate; 
        //std::unordered_map<std::string, IAction*> action_map;

        //Renderer Engine_Renderer;
        //bool isRunning; //If set to false, this will end the 3D engine during the next engine_update()
        SDL_Event event;
        //Mesh_Pipeline mesh_pipeline; // contains all of the objects that the engine will need to render
        //Triangle_Modifications_Pipeline tri_modifications;
        //float fTheta, tTheta;
        Camera* player_camera;
        
        std::vector<Triangle_Modifier*> modifications;
        
    public:
        Engine_3D(void);
        ~Engine_3D();
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
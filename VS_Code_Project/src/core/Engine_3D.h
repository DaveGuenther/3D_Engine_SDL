#ifndef ENGINE_3D_H
#define ENGINE_3D_H

#include <memory> // for smare ptrs

#include "GameState_Observer_Pattern.h"
#include "Frame_Rate_Manager.h"
#include "../input/Input_Parser.h"
#include "../actions/Action_Updater.h"
#include "../utility/Mesh_Pipeline.h"
#include "../materials/TextureList.h"
#include "../render/Renderer.h"
#include "../render/Camera.h"
#include "../core/Console_Variables.h"
#include "../3rd_party/bitmap_font.h"

/**
 * @brief This is the base class of the 3D engine.  It initializes the other key systems like Renderer and Input classes.  It manages updates of the various subsystems.
 * 
 */
class Engine_3D{
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

    private:

        
        std::shared_ptr<Renderer> Engine_Renderer;
        

        bool isRunning; //If set to false, this will end the 3D engine during the next engine_update()
        
        std::shared_ptr<Mesh_Pipeline> mesh_pipeline; // contains all of the objects that the engine will need to render
     
        std::shared_ptr<TextureList> texture_list; // contains all textures used by the engine.  These can be applied to meshes or used on a menu screen
        
        GameStateSubject game_state_subject;
        std::shared_ptr<Game_Engine_State_Observer> Engine_State;

        float fTheta, tTheta;
        std::shared_ptr<Input_Parser> MENU_Input_Parser;
        std::shared_ptr<Input_Parser> CONSOLE_Input_Parser;
        std::shared_ptr<Input_Parser> INWORLD_Input_Parser;
        
        BitmapFont* gameFont;
        std::shared_ptr<InGame_Action_Updater> INWORLD_Action_Updater;
        std::shared_ptr<Console_Action_Updater> CONSOLE_Action_Updater;

        std::shared_ptr<ConsoleData> consoleData;

        float FPS;
        std::shared_ptr<Frame_Rate_Manager> VariableFrameRate;

        

        SDL_Event event;

        std::shared_ptr<Camera> player_camera;
        //Camera* player_camera;
        
        std::vector<std::shared_ptr<Triangle_Modifier>> modifications;
        


};

#endif
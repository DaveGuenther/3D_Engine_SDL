#ifndef EVENT_SCANNER_H
#define EVENT_SCANNER_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include <memory>
#include "../render/Renderer.h"
#include "../core/GameState_Observer_Pattern.h"
#include "../core/Console_Variables.h"

enum input_map{PREVIOUS_MAP, CURRENT_MAP, MOUSE_BUTTON_MAP};

class Event_Scanner{

    private:
    SDL_Event event;

    std::unordered_map<std::string,bool> curr_key_matrix;
    std::unordered_map<std::string, bool> prev_key_matrix;

    std::unordered_map<std::string, bool> mouse_button_matrix;
    Game_Engine_State_Observer* Engine_State;
    GameStateSubject &game_state_subject;

    std::string current_string="";
    std::vector<std::string> command_history;

    ConsoleData* consoleData;

    /**
     * @brief This map contain four elements with keys: "MOUSE_X", "MOUSE_Y", "MOUSE_X_DELTA", "MOUSE_Y_DELTA" for the CURRENT input frame. 
     * MOUSE_X, MOUSE_Y, MOUSE_X_DELTA, and MOUSE_Y_DELTA range are all [-1.0, 1.0] unit scale
     * 
     */
    std::unordered_map<std::string, float> curr_range_input_matrix;

        /**
     * @brief This map contain four elements with keys: "MOUSE_X", "MOUSE_Y", "MOUSE_X_DELTA", "MOUSE_Y_DELTA" for the PREVIOUS input frame. 
     * MOUSE_X, MOUSE_Y, MOUSE_X_DELTA, and MOUSE_Y_DELTA range are all [-1.0, 1.0] unit scale
     * 
     */
    std::unordered_map<std::string, float> prev_range_input_matrix;

    float curr_mouse_x, curr_mouse_y, prev_mouse_x, prev_mouse_y, delta_mouse_x, delta_mouse_y;

    

    int SCREEN_W, SCREEN_H;
    std::shared_ptr<Renderer> my_renderer;

    /**
     * @brief This function is used by the getRangeMap() method and it used to establish the current mouse X and Y values as well as the delta between the X and Y values from the current and previous frame
     * 
     * It doesn't return anything, but sets the curr_range_input_matrix with updated MouseX, MouseY, DeltaX, and DeltaY values
     */
    void captureMouseMovement();


    public:
    Event_Scanner(); // Note used

    /**
     * @brief Construct a new Event_Scanner object.
     * 
     * @param my_event 
     * @param my_renderer Used in order to capture the SCREEN_W and SCREEN_H values in order to get Mouse delta values on a [-1.0,1.0] unit scale
     */
    Event_Scanner(GameStateSubject &subject, SDL_Event &my_event, std::shared_ptr<Renderer> my_renderer, ConsoleData* my_console_data);
    
    //std::string getConsoleCommand();

    /**
     * @brief This method is used to capture updates to the current and previous range and tactile input maps
     * 
     */
    void scanInput();

    /**
     * @brief Get the Tactile Map object
     * 
     * @param this_map enumerated data type with the following possible values ["PREVIOUS_MAP","CURRENT_MAP","MOUSE_BUTTON_MAP"]
     * @return const std::unordered_map<std::string,bool>&  
     */
    const std::unordered_map<std::string,bool>& getTactileMap(input_map this_map);

    /**
     * @brief Get the Range Map object
     * 
     * @param this_map enumerated data type with the following possible values ["PREVIOUS_MAP","CURRENT_MAP","MOUSE_BUTTON_MAP"]
     * @return const std::unordered_map<std::string,bool>& 
     */
    const std::unordered_map<std::string,float>& getRangeMap(input_map this_map);
    



   

};


#endif
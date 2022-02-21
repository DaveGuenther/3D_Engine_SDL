#include <SDL2/SDL.h>
#include "Event_Scanner.h"
#include <iostream>
#include <algorithm> // std::find()
#include <vector>  //std::vector
#include <filesystem> // loading key bindings
#include <fstream>

void print_map(std::unordered_map<std::string,bool> this_map);

void print_map(const std::unordered_map<std::string,bool> this_map){
    for (const std::pair<std::string,bool> this_item:this_map){
        std::cout << this_item.first << ": " << this_item.second << ", ";
    }
    std::cout << std::endl;
}

enum game_state {IN_WORLD, MENU, CONSOLE };

class IGameStateObserver{
    public:
    void update(game_state);
    
}; 

class Key_Bindings_InGame{
    public:
    void update(game_state);
    void loadInputBindings(std::string filename);

    
};

void Key_Bindings_InGame::update(game_state){
    // If you are here, game state is "IN_WORLD", and you are binding input to commands related to the IN_WORLD game_state

}

class IGameStateObservableSubject{
    public:
    virtual void setState(game_state)=0;
    virtual game_state getState()=0;
    virtual void addSubscriber(IGameStateObserver* observer)=0;
    virtual void removeSubscriber(IGameStateObserver* observer)=0;
};

class GameStateSubject:IGameStateObservableSubject{
    private:
    game_state state;
    std::vector<IGameStateObserver*> subscriber_list;    
    
    public:

    void setState(game_state state);
    game_state getState();
    void addSubscriber(IGameStateObserver* observer);
    void removeSubscriber(IGameStateObserver* observer);


};


void GameStateSubject::setState(game_state state){ this->state = state; }

game_state GameStateSubject::getState() { return this->state; }

void GameStateSubject::addSubscriber(IGameStateObserver *observer){ subscriber_list.push_back(observer); }

void GameStateSubject::removeSubscriber(IGameStateObserver* observer){ 
    std::vector<IGameStateObserver*>::iterator it;
    it = std::find (subscriber_list.begin(), subscriber_list.end(), observer);
    if (it != subscriber_list.end()){
        subscriber_list.erase(it);
    }
}



class Bindings{

    private: 
    std::unordered_map<Uint32, std::string> bindings;   
    std::string getCommand(Uint32 key_code); 

    public:
        void loadBinding(std::string filename);
        void bindKeyValuePair(std::string input_string);
        const std::unordered_map<std::string,bool> getCommandMapFromKeycodes(const std::unordered_map<Uint32,bool> keycodes);

        //void setBinding(std::pair<Uint32, std::string);


};


std::string Bindings::getCommand(Uint32 key_code){
    std::string command;
    std::unordered_map<Uint32,std::string>::iterator it; 
    it = bindings.find(key_code);
    if (it!=bindings.end()){ command=bindings.at(key_code); } else { command="NA"; }
    return command;
}

const std::unordered_map<std::string,bool> Bindings::getCommandMapFromKeycodes(const std::unordered_map<Uint32,bool> keycodes){
    std::unordered_map<std::string, bool> command_map;
    Uint32 keycode;
    std::string command;
    for (auto pair:keycodes){
        keycode=pair.first;
        command = getCommand(keycode);
        if (command !="NA") { command_map.insert_or_assign(command,true); }
    }
    return command_map;
}

void Bindings::bindKeyValuePair(std::string input_string){
	input_string.erase(std::remove_if(input_string.begin(), input_string.end(), ::isspace), input_string.end());
	std::pair<std::string,Uint32> key_value_pair;
	std::stringstream s_stream(input_string); //create string stream from the string
	
    std::string this_command, this_keycode;
	getline(s_stream, this_command, '='); //get first string delimited by comma
    getline(s_stream, this_keycode, ';');
    
    Uint32 this_int_value = static_cast<Uint32>(std::stoul(this_keycode));
    bindings.insert_or_assign(this_int_value, this_command);
} 

void Bindings::loadBinding(std::string filename){
    std::ifstream myfile;
	//filename = "Meshes/"+filename;
	std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
	myfile.open (filename);

	if (myfile.is_open()) {
        std::cout<<"File Open " << std::endl;
        std::string line;
        std::string comment = "//";
        char linefeed = '\n';
        int tri_id=0;
        while (std::getline(myfile, line)) {

            if (line.substr(0,2)!= comment) {
                // Line is not a comment
                if (line.back()!=linefeed && line.back()==';'){
                    // Line is a properly formatted, terminating with a ;
                    std::cout << line << std::endl;
                    bindKeyValuePair(line);

                }else if (line.empty()){
                    // Empty line, do nothing
                }else{
                    std::cout<< "Bad line! -> " << line << std::endl;
                }

            }
            
        }
    myfile.close();
    }
}




int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Event event;
    Renderer Engine_Renderer;
    GameStateSubject GameState;
    GameState.setState(IN_WORLD);

    Bindings in_world_bindings;
    in_world_bindings.loadBinding("config.cfg");
    

    bool is_running = true;
    Event_Scanner input_events(event, Engine_Renderer );
    while (is_running){
        input_events.scanInput();
        switch (GameState.getState()){
            case IN_WORLD:
                if (input_events.getMap(PREVIOUS_MAP)!=input_events.getMap(CURRENT_MAP)){
                    std::unordered_map<Uint32, bool> this_map = input_events.getMap(CURRENT_MAP);
                    std::unordered_map<std::string, bool> curr_command_map = in_world_bindings.getCommandMapFromKeycodes(this_map);
                    std::unordered_map<std::string, bool> prev_command_map = in_world_bindings.getCommandMapFromKeycodes(input_events.getMap(PREVIOUS_MAP));

                    if (this_map.find(SDLK_ESCAPE)!=this_map.end()){ is_running=false; }

                    std::cout << "Prev: ";
                    print_map(prev_command_map);
                    std::cout << "Curr: ";
                    print_map(curr_command_map);
                }
                break;
            default:
                if (input_events.getMap(PREVIOUS_MAP)!=input_events.getMap(CURRENT_MAP)){
                    std::unordered_map<Uint32, bool> this_map = input_events.getMap(CURRENT_MAP);
                    if (this_map.find(SDLK_ESCAPE)!=this_map.end()){ is_running=false; }
                break;
                }
        }
    }
    return 0;
}
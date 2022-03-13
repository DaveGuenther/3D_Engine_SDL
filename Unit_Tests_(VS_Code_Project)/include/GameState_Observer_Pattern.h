#ifndef GAMESTATE_OBSERVER_PATTERN_H
#define GAMESTATE_OBSERVER_PATTERN_H

#include <vector>


enum game_state {IN_WORLD, MENU, QUIT, CONSOLE };


class IGameStateObserver{
    public:
    //virtual ~IGameStateObserver(){};
    virtual void updateGameState(game_state state)=0;
    virtual game_state getGameState()=0;


    
}; 

class IGameStateObservableSubject{
    public:
    //virtual ~IGameStateObservableSubject(){};
    virtual void setState(game_state state)=0;
    virtual game_state getState()=0;
    virtual void addSubscriber(IGameStateObserver *observer)=0;
    virtual void removeSubscriber(IGameStateObserver *observer)=0;
};

class GameStateSubject:IGameStateObservableSubject{
    public:
    void setState(game_state state);
    game_state getState();
    void addSubscriber(IGameStateObserver *observer);
    void removeSubscriber(IGameStateObserver *observer);

    private:
    game_state state;
    std::vector<IGameStateObserver *> subscriber_list;  
};

/*
class Game_Input_State_Observer:public IGameStateObserver{
    public:
    Game_Input_State_Observer(GameStateSubject &subject);
    void updateGameState(game_state state);
    private:
    GameStateSubject my_subject;
    game_state state;
}; */

class Game_Engine_State_Observer:IGameStateObserver{
    private:
        GameStateSubject my_subject;
        game_state state;
    public:
        Game_Engine_State_Observer(GameStateSubject &subject);
        void updateGameState(game_state state);
        game_state getGameState();

};

#endif
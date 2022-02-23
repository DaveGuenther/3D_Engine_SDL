#ifndef GAMESTATE_OBSERVER_PATTERN_H
#define GAMESTATE_OBSERVER_PATTERN_H

#include <vector>


enum game_state {IN_WORLD, MENU, CONSOLE };


class IGameStateObserver{
    public:
    void updateGameState(game_state);
    
}; 

class IGameStateObservableSubject{
    public:
    virtual void setState(game_state)=0;
    virtual game_state getState()=0;
    virtual void addSubscriber(IGameStateObserver* observer)=0;
    virtual void removeSubscriber(IGameStateObserver* observer)=0;
};

class GameStateSubject:IGameStateObservableSubject{
    public:
    void setState(game_state state);
    game_state getState();
    void addSubscriber(IGameStateObserver* observer);
    void removeSubscriber(IGameStateObserver* observer);

    private:
    game_state state;
    std::vector<IGameStateObserver*> subscriber_list;  
};


#endif
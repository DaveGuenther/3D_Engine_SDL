#ifndef GAMESTATE_OBSERVER_PATTERN_H
#define GAMESTATE_OBSERVER_PATTERN_H

#include <vector>


enum game_state {IN_WORLD, MENU, QUIT, CONSOLE };

/**
 * @brief This is the interface for a game state Observer pattern.
 * 
 */
class IGameStateObserver{
    public:
    virtual void updateGameState(game_state state)=0;
    virtual game_state getGameState()=0;


    
}; 

/**
 * @brief This is the interface for a subject within an observer.  This subject will contain the game state.  Subscriber objects can register with the subject to be notified when the gamestate does change.
 * 
 */
class IGameStateObservableSubject{
    public:

    virtual void setState(game_state state)=0;
    virtual game_state getState()=0;
    /**
     * @brief Add a subscruber to the Gamestate Ojservable Subject
     * 
     * @param observer 
     */
    virtual void addSubscriber(IGameStateObserver *observer)=0;
    /**
     * @brief Remove a subscriber form the GameState Observable Subject
     * 
     * @param observer 
     */
    virtual void removeSubscriber(IGameStateObserver *observer)=0;
};

/**
 * @brief This is the concrete (Derived) class for the Game State Observable Subject.
 * 
 */
class GameStateSubject:IGameStateObservableSubject{
    public:
    /**
     * @brief Set the the state of the game
     * 
     * @param state This is an enumerated datatype
     */
    void setState(game_state state);
    game_state getState();
    void addSubscriber(IGameStateObserver *observer);
    void removeSubscriber(IGameStateObserver *observer);

    private:
    game_state state;
    std::vector<IGameStateObserver *> subscriber_list;  
};

/**
 * @brief This is the concrete (Derived) class of the Game State Observer.  Each object in the engine that needs to be informed of the state of the engine will have an instance of this class as an attribute.
 * 
 */
class Game_Engine_State_Observer:IGameStateObserver{
    private:
        GameStateSubject &my_subject;
        game_state state;
    public:
        Game_Engine_State_Observer(GameStateSubject &subject);
        
        /**
         * @brief This method wil be called automatically when the state of the GameStateSubject object has changed.  It will set an equivelant state in this object as a setter.
         * 
         * @param state 
         */
        void updateGameState(game_state state);
        
        
        /**
         * @brief Get the Game State object.  This simple getter will retrieve the state of the observer instance.  This method does not call the subject directly.
         * 
         * @return game_state 
         */
        game_state getGameState();

};

#endif
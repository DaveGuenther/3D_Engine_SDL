#include "core/GameState_Observer_Pattern.h"
#include <algorithm> //std::find

void GameStateSubject::setState(game_state state){ 
    this->state = state;
    for (auto subscriber:this->subscriber_list){
            subscriber->updateGameState(this->state);
    }
    
}

game_state GameStateSubject::getState() { return this->state; }

void GameStateSubject::addSubscriber(IGameStateObserver *observer){ subscriber_list.push_back(observer); }

void GameStateSubject::removeSubscriber(IGameStateObserver* observer){ 
    std::vector<IGameStateObserver*>::iterator it;
    it = std::find (subscriber_list.begin(), subscriber_list.end(), observer);
    if (it != subscriber_list.end()){
        subscriber_list.erase(it);
    }
}

Game_Engine_State_Observer::Game_Engine_State_Observer(GameStateSubject &subject){
    this->my_subject = subject;
    this->my_subject.addSubscriber(this);
}

void Game_Engine_State_Observer::updateGameState(game_state state){
    this->state = state;
}

game_state Game_Engine_State_Observer::getGameState(){ return state; }


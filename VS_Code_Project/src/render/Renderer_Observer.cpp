#include "Renderer_Observer.h"

#include <algorithm> //std::find

RendererSubject::RendererSubject(SDL_Renderer* renderer){
    this->renderer = renderer;
}

void RendererSubject::restartRenderer(SDL_Renderer* new_renderer){ 
    this->renderer = new_renderer;
    for (auto subscriber:this->subscriber_list){
            subscriber->updateRenderer(this->renderer);
    }
    
}

SDL_Renderer* RendererSubject::getSDLRendererPointer() { return this->renderer; }

void RendererSubject::addSubscriber(IRendererObserver *observer){ 
    subscriber_list.push_back(observer); 
    observer->updateRenderer(this->renderer);
    }

void RendererSubject::removeSubscriber(IRendererObserver* observer){ 
    std::vector<IRendererObserver*>::iterator it;
    it = std::find (subscriber_list.begin(), subscriber_list.end(), observer);
    if (it != subscriber_list.end()){
        subscriber_list.erase(it);
    }
}

Renderer_Observer::Renderer_Observer(RendererSubject &subject):my_subject(subject){
    //this->my_subject = subject;
    this->my_subject.addSubscriber(this);
}

void Renderer_Observer::updateRenderer(SDL_Renderer* new_renderer){
    this->renderer = new_renderer;
    
}

SDL_Renderer* Renderer_Observer::getSDLRendererPointer(){ return this->renderer; }

bool Renderer_Observer::hasRendererChanged(){ return this->hasRendererChangedSinceLastCycle;}


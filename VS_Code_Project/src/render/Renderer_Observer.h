#ifndef RENDERER_OBSERVER_H
#define RENDERER_OBSERVER_H


#include <vector>

#include <SDL2/SDL.h>

/**
 * The SDL_Renderer object is sent to MANY parts of the engine.  Should the SDL_Renderer need to be destroyed and recreated (such as from changing resolutions or window/fullscreen)
 * then this object will help manage all objects that contain a pointer to the SDL_Renderer.  If the renderer is restarted, then the objserver will call an update function in each 
 * of those parts of the engine that use the renderer to update their pointers, and in some cases rerun part of their specific logic (such as the TexturePNG classes that rely on 
 * a header only implementation for PNG images that requires an active renderer to work.)
*/
/**
 * @brief This is the interface for a game state Observer pattern.
 * 
 */
class IRendererObserver{
    public:
    virtual void updateRenderer(SDL_Renderer* new_renderer)=0;
    virtual SDL_Renderer* getSDLRendererPointer()=0;   
    virtual bool hasRendererChanged()=0; 
}; 

/**
 * @brief This is the interface for a subject within an observer.  This subject will contain the game state.  Subscriber objects can register with the subject to be notified when the gamestate does change.
 * 
 */
class IRendererObservableSubject{
    public:

    virtual void restartRenderer(SDL_Renderer* new_renderer)=0;
    virtual SDL_Renderer* getSDLRendererPointer()=0;
    /**
     * @brief Add a subscruber to the Gamestate Ojservable Subject
     * 
     * @param observer 
     */
    virtual void addSubscriber(IRendererObserver *observer)=0;
    /**
     * @brief Remove a subscriber form the GameState Observable Subject
     * 
     * @param observer 
     */
    virtual void removeSubscriber(IRendererObserver *observer)=0;
};

/**
 * @brief This is the concrete (Derived) class for the Game State Observable Subject.
 * 
 */
class RendererSubject:IRendererObservableSubject{
    public:
    /**
     * @brief Set the the state of the game
     * 
     * @param state This is an enumerated datatype
     */
    RendererSubject(SDL_Renderer* renderer);
    void restartRenderer(SDL_Renderer* new_renderer);
    SDL_Renderer* getSDLRendererPointer();
    void addSubscriber(IRendererObserver *observer);
    void removeSubscriber(IRendererObserver *observer);

    private:
    SDL_Renderer* renderer;
    std::vector<IRendererObserver *> subscriber_list;  
};

/**
 * @brief This is the concrete (Derived) class of the Game State Observer.  Each object in the engine that needs to be informed of the state of the engine will have an instance of this class as an attribute.
 * 
 */
class Renderer_Observer:IRendererObserver{
    private:
        RendererSubject &my_subject;
        SDL_Renderer* renderer=NULL;
        bool hasRendererChangedSinceLastCycle=false;
    public:
        Renderer_Observer(RendererSubject &subject);
        
        /**
         * @brief This method wil be called automatically when the state of the GameStateSubject object has changed.  It will set an equivelant state in this object as a setter.
         * 
         * @param state 
         */
        void updateRenderer(SDL_Renderer* new_renderer);
        
        
        /**
         * @brief Get the Game State object.  This simple getter will retrieve the state of the observer instance.  This method does not call the subject directly.
         * 
         * @return game_state 
         */
        SDL_Renderer* getSDLRendererPointer();

        bool hasRendererChanged();

};







#endif
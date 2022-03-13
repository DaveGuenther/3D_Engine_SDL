#ifndef FRAME_RATE_MANAGER_H
#define FRAME_RATE_MANAGER_H

#include <SDL2\SDL.h>

class Frame_Rate_Manager{
    private:
        float FPS;
        Uint64 frameStart;
        Uint64 frameEnd;
        int timeDelta;
        float frameDelay;

    public:
        Frame_Rate_Manager(float FPS){
            this->FPS = FPS;
            this->frameDelay = 1000.0f/FPS;
        }

        void setFrameStart(){ frameStart = SDL_GetTicks64(); }

        void setFrameEnd(){ frameEnd = SDL_GetTicks64(); }

        void delay(){
            timeDelta = frameEnd-frameStart;
            if (frameDelay > timeDelta) { SDL_Delay(frameDelay - timeDelta); }
        }

};

#endif
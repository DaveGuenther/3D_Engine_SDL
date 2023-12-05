#include "Frame_Rate_Manager.h"

Frame_Rate_Manager::Frame_Rate_Manager(float FPS){
    {
        this->FPS = FPS;
        this->frameDelay = 1000.0f/FPS;
    }
}

void Frame_Rate_Manager::setFrameStart(){ frameStart = SDL_GetTicks64(); }

void Frame_Rate_Manager::setFrameEnd(){ frameEnd = SDL_GetTicks64(); }

void Frame_Rate_Manager::delay(){
            timeDelta = frameEnd-frameStart;
            measured_FPS = 1000.0f/timeDelta;
            if (frameDelay > timeDelta) { 
                SDL_Delay(frameDelay - timeDelta); 
                measured_FPS =60.0f;
                }
        }

const float Frame_Rate_Manager::getMeasuredFPS(){ return measured_FPS; }
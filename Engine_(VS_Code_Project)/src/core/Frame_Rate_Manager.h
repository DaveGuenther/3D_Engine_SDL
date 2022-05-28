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
        float measured_FPS;

    public:
        Frame_Rate_Manager(float FPS){
            this->FPS = FPS;
            this->frameDelay = 1000.0f/FPS;
        }

        /**
         * @brief Captures the timestamp of the start of the frame.  Used to determine if a delay is required
         * 
         */
        void setFrameStart(){ frameStart = SDL_GetTicks64(); }

        /**
         * @brief Captured the timestamp of the end of a frame.  Used to determine if a delay is required
         * 
         */
        void setFrameEnd(){ frameEnd = SDL_GetTicks64(); }

        /**
         * @brief This function will determine if the last frame was completed faster than 1/FPS seconds.
         * If the frame was completed faster, than it will delay here for the remainder of 1/FPS seconds.  This
         * function does not yet account for frame drops of the frame takes longer than 1/FPS seconds to complete.
         * 
         */
        void delay(){
            timeDelta = frameEnd-frameStart;
            measured_FPS = 1000.0f/timeDelta;
            if (frameDelay > timeDelta) { SDL_Delay(frameDelay - timeDelta); }
        }

        const float getMeasuredFPS(){ return measured_FPS; }

};

#endif
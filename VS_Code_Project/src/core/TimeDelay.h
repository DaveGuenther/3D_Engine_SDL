#ifndef TIMEDELAY_H
#define TIMEDELAY_H

#include <SDL2/SDL.h>

class TimeDelay{
    public:
        TimeDelay() {this->timerComplete=true;}
        void setTimer(Uint64 milliseconds){
            this->milliseconds = milliseconds;
            
        }

        void startTimer (){
            this->timerComplete = false;
            this->timer_start  = SDL_GetTicks64();
        }

        bool isFinished(){
            if ((SDL_GetTicks64() - timer_start)>=milliseconds){
                timerComplete=true;
            }
            return timerComplete;
        }

    private:
        Uint64 milliseconds;
        Uint64 timer_start;
        Uint64 timer_end;
        bool timerComplete;
};

#endif
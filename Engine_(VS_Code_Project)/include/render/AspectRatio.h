#ifndef ASPECTRATIO_H
#define ASPECTRATIO_H

class AspectRatio{
    public:
        static float getAspectRatio(float SCREEN_W, float SCREEN_H){
            return float(float(SCREEN_H)/float(SCREEN_W));
        }
};

#endif
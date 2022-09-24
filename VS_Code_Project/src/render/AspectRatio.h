#ifndef ASPECTRATIO_H
#define ASPECTRATIO_H

/**
 * @brief This class provides a globally available method to calculate the aspect ratio of the screen and frustum.  
 * It may eventually be refactored into an observer pattern
 * 
 */
class AspectRatio{
    public:
        /**
         * @brief Get the Aspect Ratio of the screen dimensions in pixels
         * 
         * @param SCREEN_W could by int or float 
         * @param SCREEN_H coult be int of float
         * @return float
         */
        static float getAspectRatio(float SCREEN_W, float SCREEN_H);
};

#endif
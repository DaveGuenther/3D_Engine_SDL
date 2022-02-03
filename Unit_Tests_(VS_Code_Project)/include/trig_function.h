#ifndef TRIG_FUNCTION_H
#define TRIG_FUNCTION_H
#include <math.h>

class Trig_Function{
    public:
        virtual float get(float deg_angle)=0;
    protected:
        float function[360];
        const float PI=3.14159265f;

};

class Deg_Sin : public Trig_Function{
    public:
        Deg_Sin(){
            for (int i=0;i<360;i++){
                function[i]=SDL_sinf(i*(PI/180.0f));
            }

        }

        float get(float deg_angle){
            float ret_val;
            int deg_int_angle=nearbyint(deg_angle);
            if (deg_int_angle==0){ ret_val = function[0]; }else { deg_int_angle %= 360; }
            if (deg_int_angle<0){ret_val = -function[deg_int_angle];} else {ret_val = function[deg_int_angle];}

            return ret_val;
        } 


};


class Deg_Cos : public Trig_Function{
    public:
        Deg_Cos(){
            for (int i=0;i<360;i++){
                function[i]=cos(i*(PI/180.0f));
            }

        }

        float get(float deg_angle){
            float ret_val;
            int deg_int_angle=nearbyint(deg_angle);
            if (deg_int_angle==0){ ret_val = function[0]; }else { deg_int_angle %= 360; }
            if (deg_int_angle<0){ret_val = -function[deg_int_angle];} else {ret_val = function[deg_int_angle];}

            return ret_val;
        } 
           

};

#endif
#include "nonVector_Math_Service.h"

float nonVectorMathService::lerp(float x, float y, float t){
    float lerp_val=0.0f;
    if (x>y){
        lerp_val = (x-y)*t +y;
    }else{
        lerp_val = (y-x)*t +x;
    }

    return lerp_val;
}
#include "Mat4x4.h"
#include <string>

Mat4x4::Mat4x4(){
    // Initialize empty 4x4 matrix to 0.0f
    for (int x=0;x<4;x++){
        for (int y=0;y<4;y++){
            m[x][y] = 0.0f;
        }
    }
        
}

std::string Mat4x4::toString(){
    std::string ret_val = "{{"+std::to_string(m[0][0]) +", "+std::to_string(m[0][1])+", "+std::to_string(m[0][2])+", "+std::to_string(m[0][3])+ "},\n"+
                            "{"+std::to_string(m[1][0]) +", "+std::to_string(m[1][1])+", "+std::to_string(m[1][2])+", "+std::to_string(m[1][3])+ "},\n"+
                            "{"+std::to_string(m[2][0]) +", "+std::to_string(m[2][1])+", "+std::to_string(m[2][2])+", "+std::to_string(m[2][3])+ "},\n"+
                            "{"+std::to_string(m[3][0]) +", "+std::to_string(m[3][1])+", "+std::to_string(m[3][2])+", "+std::to_string(m[3][3])+ "}}";
    return ret_val;
}
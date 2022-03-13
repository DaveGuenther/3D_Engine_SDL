#include "Triangle_Modifications_Pipeline.h"

Triangle_Modifications_Pipeline::Triangle_Modifications_Pipeline(){

}

void Triangle_Modifications_Pipeline::Add_Translation(float x, float y, float z){
    Translator this_translation(x, y, z);
    modifications.push_back(this_translation);
}


void Triangle_Modifications_Pipeline::Add_Rotation(float x, float y, float z, Vec3d center){
    Rotator this_rotation(x, y, z, center);
    modifications.push_back(this_rotation);

}

const std::vector<Triangle_Modifier>& Triangle_Modifications_Pipeline::getModifications(){
    return modifications;
}
#include "Triangle_Modifications_Pipeline.h"

Triangle_Modifications_Pipeline::Triangle_Modifications_Pipeline(){

}

void Triangle_Modifications_Pipeline::Add_Translation(float x, float z){
    Translator this_translation(x, z);
    modifications.push_back(this_translation);
}


void Triangle_Modifications_Pipeline::Add_Rotation(float x, float z, Vec3d center){
    Rotator this_rotation(x, z, center);
    modifications.push_back(this_rotation);

}

const std::vector<Triangle_Modifier>& Triangle_Modifications_Pipeline::getModifications(){
    return modifications;
}
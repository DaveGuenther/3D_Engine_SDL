#include <string>
#include "objects/OBJ_Parse.h"
#include "objects/OBJ.h"
#include "utility/Mesh.h"
#include "utility/Triangle.h"


OBJ::OBJ(std::string filename){
    OBJ_Parse this_OBJ(filename);
    Mesh thisMesh(0);
    int tri_id=0;
    for (auto triangle: this_OBJ.triangleFaces){
        Triangle thisTri;
        std::vector<int> vertIDs = triangle.getVertexIDs();
        for (int i=0;i<3;i++){
            int vertex_ID = vertIDs[i]-1;
            Vec3d this_vert = Vec3d(this_OBJ.vertices[vertex_ID].getX(),
                                    this_OBJ.vertices[vertex_ID].getY(),
                                    this_OBJ.vertices[vertex_ID].getZ());
            thisTri.setTrianglePoint(i,this_vert);
            
        }
        thisTri.setID(tri_id);
        thisMesh.add3dTriangle(thisTri);
        tri_id+=1;
        
    }
    this->thisMesh=thisMesh;
    /*
    for each tri in faces vector
        add vertexes to tri
        add texture coords to tri
        add face to tris vector

    build Mesh from vector of tris
    */

}

Mesh& OBJ::getMesh(){
    return thisMesh;
}
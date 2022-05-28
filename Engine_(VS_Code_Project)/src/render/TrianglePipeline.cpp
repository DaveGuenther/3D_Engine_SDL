#include <algorithm>
#include <memory>

#include "TrianglePipeline.h"
#include "utility/Mesh_Pipeline.h"


TrianglePipeline::TrianglePipeline(){
    

    
}

void TrianglePipeline::setPipelineFromMeshes(std::shared_ptr<Mesh_Pipeline> my_pipeline){
    for (auto this_mesh:my_pipeline->Get_Meshes()){
        for (auto this_tri:this_mesh.getTriangles()){
            this->tri_pipeline.push_back(this_tri);
        }
    }
}

void TrianglePipeline::setPipelineFromTriangles(std::vector<Triangle> this_tri_pipeline){
    this->tri_pipeline = this_tri_pipeline;
}

void TrianglePipeline::orderPipelineByZ(){ 
    sort(this->tri_pipeline.begin(), this->tri_pipeline.end(), zSortFunction); 
}

std::vector<Triangle> TrianglePipeline::getTrianglePipeline(){
    return this->tri_pipeline;
}

bool TrianglePipeline::zSortFunction(Triangle a, Triangle b){
    return (a.getTriangleZCenter() > b.getTriangleZCenter());
}


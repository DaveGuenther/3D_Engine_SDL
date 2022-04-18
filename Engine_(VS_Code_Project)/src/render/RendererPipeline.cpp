#include <algorithm>

#include "render/RendererPipeline.h"
#include "utility/Mesh_Pipeline.h"


RendererPipeline::RendererPipeline(Mesh_Pipeline* my_pipeline){
    
    for (auto this_mesh:my_pipeline->Get_Meshes()){
        for (auto this_tri:this_mesh.getTriangles()){
            this->tri_pipeline.push_back(this_tri);
        }
    }
    
}


void RendererPipeline::orderPipelineByZ(){ 
    sort(this->tri_pipeline.begin(), this->tri_pipeline.end(), zSortFunction); 
}

std::vector<Triangle> RendererPipeline::getTrianglePipeline(){
    return this->tri_pipeline;
}

bool RendererPipeline::zSortFunction(Triangle a, Triangle b){
    return (a.getTriangleZCenter() > b.getTriangleZCenter());
}


#ifndef TRIANGLE_PIPELINE_H
#define TRIANGLE_PIPELINE_H

#include "utility/Mesh_Pipeline.h"
#include "utility/Triangle.h"
#include "render/Camera.h"
#include <vector>

/**
 * @brief This class extracts all triangles from the Mesh Pipeline and organizes them into a triangle pipeline in order to start the pre-render process
 * specifically for renderering and nothing else.  This class will also order the triangles from z-far to z-near so they can be drawn properly
 * 
 */
class TrianglePipeline{
    public:
    /**
     * @brief Construct a new Renderer Pipeline object.  It populates the private attribuate tri_pipeline with all triangles across all meshes
     * 
     * 
     * @param my_pipeline This is a Mesh_Pipeline*
     */
    TrianglePipeline();

    void setPipelineFromMeshes(Mesh_Pipeline* my_pipeline);

    void setPipelineFromTriangles(std::vector<Triangle> this_tri_pipeline);

    /**
     * @brief Orders the triangles in the triangle pipeline by z value from far to near
     * 
     */
    void orderPipelineByZ();

    /**
     * @brief Returns the triangle pipeline object
     * 
     * @return std::vector<Triangle> 
     */
    std::vector<Triangle> getTrianglePipeline();

    private:
    /**
     * @brief This vector contains triangles ordered by Z value descending
     * 
     */
    std::vector<Triangle> tri_pipeline;

    /**
     * @brief This function is used by the sort function in the class constructor. It is called for each element comparison made by the sort function.
     * Two triangles are passed in and the function compares their Z values returning a boolean true if they need to be swapped of false if they don't need to be swapped.
     * 
     * 
     * @param a
     * @param b 
     * @return true if the triangle positions need to be swapped in the vector
     * @return false if the triangle positions don't need to be swapped
     */
    static bool zSortFunction(Triangle a, Triangle b);

    private:
        Vec3d camera_pos;
};

#endif
#ifndef PRERENDERER_H
#define PRERENDERER_H

#include "utility/Mesh_Pipeline.h"
#include "utility/Triangle.h"
#include <vector>

/**
 * @brief This class extracts all triangles from the Mesh Pipeline and organizes them into a triangle pipeline
 * specifically for renderering and nothing else.  This class will also order the triangles from z-far to z-near so they can be drawn properly
 * 
 */
class RendererPipeline{
    public:
    /**
     * @brief Construct a new Renderer Pipeline object.  It populates the private attribuate tri_pipeline with all triangles across all meshes
     * ordered by z value from far to near
     * 
     * @param my_pipeline This is a Mesh_Pipeline*
     */
    RendererPipeline(Mesh_Pipeline* my_pipeline);

    /**
     * @brief Get the Ordered Triangles object
     * 
     * @return std::vector<Triangle> 
     */
    std::vector<Triangle> getOrderedTriangles();

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
};

#endif
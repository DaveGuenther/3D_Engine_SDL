#include "Rotator_Service.h"
#include <SDL2/SDL.h>
#include "Multiply_Matrix_Service.h"
#include "Mat4x4.h"

Mat4x4 Rotator_Service::Calculate_Rotation_Z_Matrix(float fTheta, float tTheta){

    Mat4x4 mat_ZRot;
    // Z Rotation Matrix
    mat_ZRot.m[0][0] = SDL_cosf(fTheta*(3.14159265/180.0));
    mat_ZRot.m[0][1] = SDL_sinf(fTheta*(3.14159265/180.0));
    mat_ZRot.m[1][0] = -SDL_sinf(fTheta*(3.14159265/180.0));
    mat_ZRot.m[1][1] = SDL_cosf(fTheta*(3.14159265/180.0));
    mat_ZRot.m[2][2] = 1;
    mat_ZRot.m[3][3] = 1;
    return mat_ZRot;
}

Mat4x4 Rotator_Service::Calculate_Rotation_X_Matrix(float fTheta, float tTheta){
    Mat4x4 mat_XRot;
    // X Rotation Matrix
    mat_XRot.m[0][0] = 1;
    mat_XRot.m[1][1] = SDL_cosf(tTheta/2*(3.14159265/180.0));
    mat_XRot.m[1][2] = SDL_sinf(tTheta/2*(3.14159265/180.0));
    mat_XRot.m[2][1] = -SDL_sinf(tTheta/2*(3.14159265/180.0));
    mat_XRot.m[2][2] = SDL_cosf(tTheta/2*(3.14159265/180.0));
    mat_XRot.m[3][3] = 1;	    
    return mat_XRot;
}


void Rotator_Service::Rotate_Pipeline(Mesh_Pipeline &this_mesh_pipeline){
    
    //  Currently all rotations made here are lost at the end because this_mesh_pipeline is not being updated.  Fix this bug.


    // Figure out how to get it so that edits made to this_mesh make it back to this_mesh_pipeline
    std::vector<Mesh>& Meshes = this_mesh_pipeline.Get_Meshes();
    for (auto& this_mesh: Meshes){
        float fTheta = this_mesh.get_fTheta();
        float tTheta = this_mesh.get_tTheta();
        std::vector<Triangle>& tris = this_mesh.get_tris();
        // figure out how to get it so that edits made to tri or tris gets updated into this_mesh and then into this_mesh_pipeline.
        for (auto& tri: tris)
        {
            Mat4x4 mat_ZRot, mat_XRot;
            mat_ZRot = Calculate_Rotation_Z_Matrix(fTheta, tTheta);
            mat_XRot = Calculate_Rotation_X_Matrix(fTheta, tTheta);
            
			// Apply Perspective Projection Matrix
			Triangle triRotated_Z, triRotated_ZX;
			
			Multiply_Matrix_Service::MultiplyMatrixVector(tri.p[0], triRotated_Z.p[0], mat_ZRot);
			Multiply_Matrix_Service::MultiplyMatrixVector(tri.p[1], triRotated_Z.p[1], mat_ZRot);
			Multiply_Matrix_Service::MultiplyMatrixVector(tri.p[2], triRotated_Z.p[2], mat_ZRot);
			
			Multiply_Matrix_Service::MultiplyMatrixVector(triRotated_Z.p[0], triRotated_ZX.p[0], mat_XRot);
			Multiply_Matrix_Service::MultiplyMatrixVector(triRotated_Z.p[1], triRotated_ZX.p[1], mat_XRot);
			Multiply_Matrix_Service::MultiplyMatrixVector(triRotated_Z.p[2], triRotated_ZX.p[2], mat_XRot);	            
        
            tri.p[0]=triRotated_ZX.p[0];
            tri.p[1]=triRotated_ZX.p[1];
            tri.p[2]=triRotated_ZX.p[2];
        }
    }   
}
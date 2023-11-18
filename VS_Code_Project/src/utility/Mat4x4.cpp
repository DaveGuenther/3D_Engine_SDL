#include <string>
#include <SDL2/SDL.h>

#include "../utility/Mat4x4.h"
#include "../utility/Vector_Math_Service.h"

const float PI_by_180 = 3.14159265/180.0;

Mat4x4::Mat4x4(){
    // Initialize empty 4x4 matrix to 0.0f
    for (int x=0;x<4;x++){
        for (int y=0;y<4;y++){
            m[x][y] = 0.0f;
        }
    }
        
}

Mat4x4::Mat4x4(const Mat4x4 &m_in){
    for (int x=0;x<4;x++){
        for(int y=0;y<4;y++){
            m[x][y] = m_in.m[x][y];
        }
    }
}

Mat4x4 Mat4x4::matrixMakeIdentify(){
    Mat4x4 matrix;
    matrix.m[0][0]=1.0f;
    matrix.m[1][1]=1.0f;
    matrix.m[2][2]=1.0f;
    matrix.m[3][3]=1.0f;
    return matrix;
}

Mat4x4 Mat4x4::matrixMakeRotationX(float x_degs){
    Mat4x4 mat_XRot;
    //X Rotation MAtrix
    mat_XRot.m[0][0] = 1;
    mat_XRot.m[0][1] = 0;
    mat_XRot.m[0][2] = 0;
    mat_XRot.m[0][3] = 0;

    mat_XRot.m[1][0] = 0;
    mat_XRot.m[1][1] = SDL_cosf(x_degs*(PI_by_180));
    mat_XRot.m[1][2] = SDL_sinf(x_degs*(PI_by_180));
    mat_XRot.m[1][3] = 0;

    mat_XRot.m[2][0] = 0;
    mat_XRot.m[2][1] = -SDL_sinf(x_degs*(PI_by_180));
    mat_XRot.m[2][2] = SDL_cosf(x_degs*(PI_by_180));
    mat_XRot.m[2][3] = 0;

    mat_XRot.m[3][0] = 0;
    mat_XRot.m[3][1] = 0;
    mat_XRot.m[3][2] = 0;
    mat_XRot.m[3][3] = 1;
    return mat_XRot;
}

Mat4x4 Mat4x4::matrixMakeRotationY(float y_degs){
    Mat4x4 mat_YRot;
    //Y Rotation MAtrix
    mat_YRot.m[0][0] = SDL_cosf(y_degs*(PI_by_180));
    mat_YRot.m[0][1] = 0;
    mat_YRot.m[0][2] = -SDL_sinf(y_degs*(PI_by_180));
    mat_YRot.m[0][3] = 0;

    mat_YRot.m[1][0] = 0;
    mat_YRot.m[1][1] = 1;
    mat_YRot.m[1][2] = 0;
    mat_YRot.m[1][3] = 0;

    mat_YRot.m[2][0] = SDL_sinf(y_degs*(PI_by_180));
    mat_YRot.m[2][1] = 0;
    mat_YRot.m[2][2] = SDL_cosf(y_degs*(PI_by_180));
    mat_YRot.m[2][3] = 0;

    mat_YRot.m[3][0] = 0;
    mat_YRot.m[3][1] = 0;
    mat_YRot.m[3][2] = 0;
    mat_YRot.m[3][3] = 1;
    return mat_YRot;

}

Mat4x4 Mat4x4::matrixMakeRotationZ(float z_degs){
    Mat4x4 mat_ZRot;
    //Z Rotation Matrix
    mat_ZRot.m[0][0] = SDL_cosf(z_degs*(PI_by_180));
    mat_ZRot.m[0][1] = SDL_sinf(z_degs*(PI_by_180));
    mat_ZRot.m[0][2] = 0;
    mat_ZRot.m[0][3] = 0;

    mat_ZRot.m[1][0] = -SDL_sinf(z_degs*(PI_by_180));
    mat_ZRot.m[1][1] = SDL_cosf(z_degs*(PI_by_180));
    mat_ZRot.m[1][2] = 0;
    mat_ZRot.m[1][3] = 0;

    mat_ZRot.m[2][0] = 0;
    mat_ZRot.m[2][1] = 0;
    mat_ZRot.m[2][2] = 1;
    mat_ZRot.m[2][3] = 0;

    mat_ZRot.m[3][0] = 0;
    mat_ZRot.m[3][1] = 0;
    mat_ZRot.m[3][2] = 0;
    mat_ZRot.m[3][3] = 1;
    return mat_ZRot;
}

Mat4x4 Mat4x4::matrixMakeTranslation(float x, float y, float z){
    Mat4x4 matrix;
    matrix.m[0][0] = 1.0f;
    matrix.m[0][1] = 0.0f;
    matrix.m[0][2] = 0.0f;    
    matrix.m[0][3] = 0.0f;

    matrix.m[1][0] = 0.0f;
    matrix.m[1][1] = 1.0f;
    matrix.m[1][2] = 0.0f;
    matrix.m[1][3] = 0.0f;

    matrix.m[2][0] = 0.0f;
    matrix.m[2][1] = 0.0f;
    matrix.m[2][2] = 1.0f;
    matrix.m[2][3] = 0.0f;


    matrix.m[3][0] = x;
    matrix.m[3][1] = y;
    matrix.m[3][2] = z;
    matrix.m[3][3] = 1.0f;
    return matrix;

}

Mat4x4 Mat4x4::matrixMakeProjection(float fFOV, int SCREEN_W, int SCREEN_H, float fNear, float fFar){

	float fAspectRatio = (float)SCREEN_H/(float)SCREEN_W;
	float fFOV_rad = 1.0/(SDL_tanf((fFOV/2)*(PI_by_180)));
    Mat4x4 matProj;
	matProj.m[0][0] = fAspectRatio*fFOV_rad;
	matProj.m[1][0] = 0.0;
	matProj.m[2][0] = 0.0;
	matProj.m[3][0] = 0.0;
	matProj.m[0][1] = 0.0;
	matProj.m[1][1] = fFOV_rad;
	matProj.m[2][1] = 0.0;
	matProj.m[3][1] = 0.0;
	matProj.m[0][2] = 0.0;
	matProj.m[1][2] = 0.0;
	matProj.m[2][2] = fFar/(fFar-fNear);
	matProj.m[3][2] = (-fFar*fNear)/(fFar-fNear);
	matProj.m[0][3] = 0.0;
	matProj.m[1][3] = 0.0;
	matProj.m[2][3] = 1.0;
	matProj.m[3][3] = 0.0;
    return matProj;
}

Mat4x4 Mat4x4::matrixMatrixMultiplication(Mat4x4& m1, Mat4x4& m2){
    Mat4x4 matrix;
    for (int c=0; c<4; c++){
        for(int r=0;r<4;r++){
            matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
        }
    }
    return matrix;
}

Mat4x4 Mat4x4::matrixPointAt(Vec3d& pos, Vec3d& target, Vec3d& up){
    
    //Calculate new forward direction
    Vec3d new_forward = target-pos;
    VectorMathService::getUnitVector(new_forward);

    //Calculate new Up vector   (I don't yet understand why we need to do this)
    float up_projection_on_new_forward = VectorMathService::dotProduct(up, new_forward);
    Vec3d a = new_forward * up_projection_on_new_forward;
    Vec3d new_up = up-a;
    VectorMathService::getUnitVector(new_up);

    // Create new Right vector
    Vec3d new_right = VectorMathService::crossProduct(new_up, new_forward);

    // Construct POINT AT matrix

// Construct Dimensioning and Translation Matrix	
    Mat4x4 matrix;
    matrix.m[0][0] = new_right.x;	    matrix.m[0][1] = new_right.y;	    matrix.m[0][2] = new_right.z;	    matrix.m[0][3] = 0.0f;
    matrix.m[1][0] = new_up.x;		    matrix.m[1][1] = new_up.y;		    matrix.m[1][2] = new_up.z;		    matrix.m[1][3] = 0.0f;
    matrix.m[2][0] = new_forward.x;	    matrix.m[2][1] = new_forward.y;	    matrix.m[2][2] = new_forward.z;	    matrix.m[2][3] = 0.0f;
    matrix.m[3][0] = pos.x;			    matrix.m[3][1] = pos.y;			    matrix.m[3][2] = pos.z; 			matrix.m[3][3] = 1.0f;
    return matrix;

}

Mat4x4 Mat4x4::matrixLookAt(Mat4x4& m){
    Mat4x4 matrix;
    matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
    matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
    matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
    matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
    matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
    matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
    matrix.m[3][3] = 1.0f;

    return matrix;
}


std::string Mat4x4::toString(){
    std::string ret_val = "{{"+std::to_string(m[0][0]) +", "+std::to_string(m[0][1])+", "+std::to_string(m[0][2])+", "+std::to_string(m[0][3])+ "},\n"+
                            "{"+std::to_string(m[1][0]) +", "+std::to_string(m[1][1])+", "+std::to_string(m[1][2])+", "+std::to_string(m[1][3])+ "},\n"+
                            "{"+std::to_string(m[2][0]) +", "+std::to_string(m[2][1])+", "+std::to_string(m[2][2])+", "+std::to_string(m[2][3])+ "},\n"+
                            "{"+std::to_string(m[3][0]) +", "+std::to_string(m[3][1])+", "+std::to_string(m[3][2])+", "+std::to_string(m[3][3])+ "}}";
    return ret_val;
}
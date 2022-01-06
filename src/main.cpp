#include <iostream>
#include <vector>
#include <SDL2/SDL.h>


int SCREEN_W = 640;
int SCREEN_H = 360;

struct vec3d
{
	float x,y,z;
};

struct triangle
{
	vec3d p[3];
};

struct mesh
{
	std::vector<triangle> tris;
};

struct mat4x4
{
	float m[4][4]={0};
};

struct vec2d
{
	float x;
	float y;
};

vec2d cart_to_screen(vec2d this_point)
{
	float HALF_SCREEN_W = (SCREEN_W)/2;
	float scaled_x = this_point.x*(HALF_SCREEN_W);
	this_point.x = scaled_x+(HALF_SCREEN_W);

	float HALF_SCREEN_H = (SCREEN_H)/2;
	float scaled_y = this_point.y*(HALF_SCREEN_H);
	this_point.y = SCREEN_H-(scaled_y+(HALF_SCREEN_H));
	return this_point;
} 

void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m)
{
	//[x, y, z, 1] * mat4x4 gives us 1x4 vector
	
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];


	// Convert from 1x4 to 1x3 matrix
	if (w!=0)
	{
		o.x=o.x/w;
		o.y=o.y/w;
		o.z=o.z/w;
	}

}

void DrawTriangle(SDL_Renderer *renderer, vec2d vert1, vec2d vert2, vec2d vert3, SDL_Color col)
{
	
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);

	vert1 = cart_to_screen(vert1);
	vert2 = cart_to_screen(vert2);
	vert3 = cart_to_screen(vert3);
	SDL_RenderDrawLineF(renderer, vert1.x, vert1.y, vert2.x, vert2.y);
	SDL_RenderDrawLineF(renderer, vert2.x, vert2.y, vert3.x, vert3.y);
	SDL_RenderDrawLineF(renderer, vert3.x, vert3.y, vert1.x, vert1.y);
}

int main(int argv, char** args)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	float fTheta, tTheta=45.0f;

	// Projection Matrix
	float fNear = 0.1;
	float fFar = 1000.0;
	float fFOV=90.0;
	float fAspectRatio = (float)SCREEN_H/(float)SCREEN_W;
	float fFOV_rad = 1.0/(SDL_tanf((fFOV/2)*(3.14159265/180.0)));

	mat4x4 matProj, mat_XRot, mat_ZRot;  //[row][column]
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
	



	// define cube in 3D space made up of triangles.  tris are drawn in clockwise order when facing the triangle
	mesh meshCube;
	meshCube.tris = {
		//South
		{0,0,0,		0,1,0,		1,1,0},
		{0,0,0,		1,1,0,		1,0,0},

		//East
		{1,0,0,		1,1,0,		1,1,1},
		{1,0,0,		1,1,1,		1,0,1},

		//North
		{1,0,1,		1,1,1,		0,1,1},
		{1,0,1,		0,1,1,		0,0,1},

		//West
		{0,0,1,		0,1,1,		0,1,0},
		{0,0,1,		0,1,0,		0,0,0},

		//Top
		{0,1,0,		0,1,1,		1,1,1},
		{0,1,0,		1,1,1,		1,1,0},

		//Bottom
		{1,0,0,		1,0,1,		0,0,1},
		{1,0,0,		0,0,1,		0,0,0}
	};

	SDL_Window *window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	bool isRunning = true;
	SDL_Event event;

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					isRunning = false;
				}

				if (event.key.keysym.sym == SDLK_RIGHT)
				{
					fTheta +=1;
					
				}
				
				if (event.key.keysym.sym == SDLK_LEFT)
				{
					fTheta -=1;
					
				}

				if (event.key.keysym.sym == SDLK_UP)
				{
					tTheta +=1;
					
				}
				
				if (event.key.keysym.sym == SDLK_DOWN)
				{
					tTheta -=1;
					
				}
			}
		}
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);


		// Z Rotation Matrix
		mat_ZRot.m[0][0] = SDL_cosf(fTheta*(3.14159265/180.0));
		mat_ZRot.m[0][1] = SDL_sinf(fTheta*(3.14159265/180.0));
		mat_ZRot.m[1][0] = -SDL_sinf(fTheta*(3.14159265/180.0));
		mat_ZRot.m[1][1] = SDL_cosf(fTheta*(3.14159265/180.0));
		mat_ZRot.m[2][2] = 1;
		mat_ZRot.m[3][3] = 1;

		// X Rotation Matrix
		mat_XRot.m[0][0] = 1;
		mat_XRot.m[1][1] = SDL_cosf(tTheta/2*(3.14159265/180.0));
		mat_XRot.m[1][2] = SDL_sinf(tTheta/2*(3.14159265/180.0));
		mat_XRot.m[2][1] = -SDL_sinf(tTheta/2*(3.14159265/180.0));
		mat_XRot.m[2][2] = SDL_cosf(tTheta/2*(3.14159265/180.0));
		mat_XRot.m[3][3] = 1;		
	
		SDL_Color col;
		col.r=255; col.g=0; col.b=0; col.a = 255;
		SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);

		// Draw Triangles
		for (auto tri: meshCube.tris)
		{
			// Apply Perspective Projection Matrix
			triangle triProjected, triTranslated , triRotated_Z, triRotated_ZX;
			
			MultiplyMatrixVector(tri.p[0], triRotated_Z.p[0], mat_ZRot);
			MultiplyMatrixVector(tri.p[1], triRotated_Z.p[1], mat_ZRot);
			MultiplyMatrixVector(tri.p[2], triRotated_Z.p[2], mat_ZRot);
			
			MultiplyMatrixVector(triRotated_Z.p[0], triRotated_ZX.p[0], mat_XRot);
			MultiplyMatrixVector(triRotated_Z.p[1], triRotated_ZX.p[1], mat_XRot);
			MultiplyMatrixVector(triRotated_Z.p[2], triRotated_ZX.p[2], mat_XRot);			

			triTranslated = triRotated_ZX;
			triTranslated.p[0].z = triTranslated.p[0].z+1.0;
			triTranslated.p[1].z = triTranslated.p[1].z+1.0;
			triTranslated.p[2].z = triTranslated.p[2].z+1.0;

			MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
			MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
			MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

			// Drop 3D to 2D
			vec2d point1, point2, point3;

			point1.x = triProjected.p[0].x;
			point1.y = triProjected.p[0].y;

			point2.x = triProjected.p[1].x;
			point2.y = triProjected.p[1].y;

			point3.x = triProjected.p[2].x;
			point3.y = triProjected.p[2].y;			

			//fTheta += 1.0f * fElapsedTime;

			// Draw the Triangle!
			DrawTriangle(renderer,point1, point2, point3,col);


		}

		vec2d vert1; vec2d vert2; vec2d vert3;
		vert1.x=-.40; vert1.y=-.40;
		vert2.x=.220; vert2.y=-.610;
		vert3.x=-.200; vert3.y=.700;
		//DrawTriangle(renderer, vert1, vert2, vert3, col);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		// Draw Reticle
		vec2d single_point;
		single_point.x=0;
		single_point.y=0;
		single_point = cart_to_screen(single_point);

		SDL_RenderDrawPointF(renderer, single_point.x, single_point.y);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
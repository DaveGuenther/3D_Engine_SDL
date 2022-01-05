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

void DrawTriangle(SDL_Renderer *renderer, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color col)
{
	SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
	SDL_RenderDrawLineF(renderer, x2, y2, x3, y3);
	SDL_RenderDrawLineF(renderer, x3, y3, x1, y1);
}

int main(int argv, char** args)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// Projection Matrix
	float fNear = 0.1;
	float fFar = 1000.0;
	float fFOV=90.0;
	float fAspectRatio = (float)SCREEN_H/(float)SCREEN_W;
	float fFOV_rad = 1.0/(SDL_tanf((fFOV/2)*(3.14159265/180.0)));

	mat4x4 matProj;  //[row][column]
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
			}
		}
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);


		
		/*vec2d line0, line1, single_point;
		line0.x = -1;
		line0.y = -.9;
		line1.x=1;
		line1.y=.9;


		
		line0 = cart_to_screen(line0);
		line1 = cart_to_screen(line1);
		
		*/
		
		// Draw Reticle
		vec2d single_point;
		single_point.x=.5;
		single_point.y=-.5;
		single_point = cart_to_screen(single_point);
		
		SDL_Color col;
		col.r=255; col.g=0; col.b=0; col.a = 255;
		SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
		//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		//SDL_RenderDrawLineF(renderer, line0.x, line0.y, line1.x, line1.y);

		// Draw Triangles
		for (auto tri: meshCube.tris)
		{
			triangle triProjected;
			MultiplyMatrixVector(tri.p[0], triProjected.p[0], matProj);
			MultiplyMatrixVector(tri.p[1], triProjected.p[1], matProj);
			MultiplyMatrixVector(tri.p[2], triProjected.p[2], matProj);


		}


		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);



		SDL_RenderDrawPointF(renderer, single_point.x, single_point.y);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
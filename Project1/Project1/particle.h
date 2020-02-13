#pragma once

#include "polygon.h"
#include "Circle.h"


#define NUM_MAX 500
#define FRICTION 0.96f

struct MoveParticle
{
	float x, y;
	float vx,vy;
	float radius;
	D3DCOLOR color;
};


void InitParticle();
void UninitParticle();
void UpdateParticle();
void DrawParticle(LPDIRECT3DDEVICE9 device);

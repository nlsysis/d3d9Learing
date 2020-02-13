#pragma once

#include <d3d9.h>
#include <d3dx9.h>

struct Vertex2d
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
};

struct Position
{
	float x, y;
};
struct CenterMSG
{
	Position position;
	bool isLeftDown;
};


void InitPolygon();
void UninitPolygon();
void UpdatePolygon();
void DrawPolygon(LPDIRECT3DDEVICE9 p_device);



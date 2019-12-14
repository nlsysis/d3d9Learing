#pragma once

#include <d3d9.h>
#include <d3dx9.h>

struct Vertex2d
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
};

const Vertex2d v[]
{
	{D3DXVECTOR4(200.0f,200.0f,0.0f,1.0f),D3DCOLOR_RGBA(123,253,124,255)},
	{D3DXVECTOR4(200.0f,300.0f,0.0f,1.0f),D3DCOLOR_RGBA(0,0,255,255)},
	{D3DXVECTOR4(400.0f,300.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,0,0,255)},
	{D3DXVECTOR4(200.0f,200.0f,0.0f,1.0f),D3DCOLOR_RGBA(123,253,124,255)},

};

#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

void InitPolygon();
void UninitPolygon();
void UpdatePolygon();
void DrawPolygon(LPDIRECT3DDEVICE9 p_device);



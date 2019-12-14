#pragma once
#include "D3D9.h"

typedef struct GridVertex
{
	D3DXVECTOR3 position;
	D3DCOLOR color;
};
#define FVF_GRID (D3DFVF_XYZ | D3DFVF_DIFFUSE)

void InitGrid(float sizeX, float sizeZ);
void UpdateGrid();
void DrawGrid(LPDIRECT3DDEVICE9 p_device);
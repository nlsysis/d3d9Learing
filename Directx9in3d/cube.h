#pragma once
#include "main.h"


typedef struct CubeVertex_tag
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 textCoord;
}CubeVertex;

#define FVF_CUBE (D3DFVF_XYZ  | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

void InitCube(LPDIRECT3DDEVICE9 p_device);
void UpdateCube(LPDIRECT3DDEVICE9 p_device);
void UninitCube();
void DrawCube(LPDIRECT3DDEVICE9 p_device, const D3DXMATRIX* mat);
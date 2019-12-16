#pragma once
#include "main.h"

#define FVF_Billboard (D3DFVF_XYZ | D3DFVF_TEX1)

typedef struct Billboard_tag
{
	D3DXVECTOR3 position;      //vertex
	D3DXVECTOR2 textCoord;     //uv

	Billboard_tag(D3DXVECTOR3 in_position, D3DXVECTOR2 in_textCoord)
		:
		position(in_position),
		textCoord(in_textCoord)
	{}
}Billboard;

void InitBillboard(LPDIRECT3DDEVICE9 pDevice, float sizeX, float sizeY);
void UpdateBillboard();
void DrawBillboard(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DTEXTURE9 textureBillboard,  D3DXMATRIX matWorld);
void UninitBillboard();
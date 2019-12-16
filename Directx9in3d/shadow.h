#pragma once
#include "main.h"

typedef struct Shadow_tag
{
	D3DXVECTOR3 position;      //vertex
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 textCoord;     //uv

	Shadow_tag(D3DXVECTOR3 in_position, D3DXVECTOR3 in_normal, D3DCOLOR in_color,D3DXVECTOR2 in_textCoord)
		:
		position(in_position),
		normal(in_normal),
		color(in_color),
		textCoord(in_textCoord)
	{}
}Shadow;

#define FVF_Shadow (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE| D3DFVF_TEX1)
void InitShadow(LPDIRECT3DDEVICE9 pDevice, float sizeX, float sizeZ);
void UpdateShadow();
void DrawShadow(LPDIRECT3DDEVICE9 pDevice, D3DXMATRIX matWorld);
void UninitShadow();
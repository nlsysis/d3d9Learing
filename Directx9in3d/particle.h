#pragma once
#include "main.h"

typedef struct Particle_tag
{
	D3DXVECTOR3 position;      //vertex
	D3DXVECTOR3 normal;
	D3DCOLOR	diffuse;	 // ”½ŽËŒõ
	D3DXVECTOR2 textCoord;     //uv

	Particle_tag(D3DXVECTOR3 in_position, D3DXVECTOR3 in_normal, D3DCOLOR in_color, D3DXVECTOR2 in_textCoord)
		:
		position(in_position),
		normal (in_normal),
		diffuse(in_color),
		textCoord(in_textCoord)
	{}
}Particle;

#define FVF_Particle (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE |  D3DFVF_TEX1)
void InitParticle(LPDIRECT3DDEVICE9 pDevice);
void UpdateParticle();
void DrawParticle(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DTEXTURE9 textureBillboard, D3DXMATRIX matWorld);
void UninitParticle();
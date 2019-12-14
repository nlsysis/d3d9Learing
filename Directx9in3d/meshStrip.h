#pragma once
#include "main.h"

typedef struct MeshGridVertex_tag
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 textCoord;
}MeshGridVertex;

#define FVF_MESH (D3DFVF_XYZ  | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

typedef struct MeshStrip
{
	IDirect3DVertexBuffer9 *vb_meshBuffer = nullptr;
	IDirect3DIndexBuffer9 *ib_meshBuffer = nullptr;
	LPDIRECT3DTEXTURE9 textureMesh = nullptr;
	int primCount = 0;
};
void InitGridMesh(LPDIRECT3DDEVICE9 pDevice, LPCSTR textureFileName,float width,float height, MeshStrip &in_mesh);
void  UninitGridMesh(MeshStrip &in_mesh);
void DrawGridMesh(LPDIRECT3DDEVICE9 pDevice, MeshStrip &in_mesh);
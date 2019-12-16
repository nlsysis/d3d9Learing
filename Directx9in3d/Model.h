#pragma once
#include "main.h"

struct Model
{
	LPD3DXMESH g_pMesh = NULL;   //メッシュインターフェース
	DWORD g_MaterialCount = 0;   //アテリアル数
	int *g_pTextureIds = NULL;   //テキスチャー管理番号保存用
	D3DMATERIAL9 *g_pMaterial = NULL;	
};


bool LoadModel(LPDIRECT3DDEVICE9 pDevice, LPCTSTR modelFile, LPCSTR texturePath, Model &in_model);
void UninitModel(Model &in_model);
void DrawModel(LPDIRECT3DDEVICE9 pDevice, Model &in_model);
void UpdateModel(Model &in_model);
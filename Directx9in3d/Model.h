#pragma once
#include "main.h"

enum ModelState { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };
struct Model
{
	LPD3DXMESH g_pMesh = NULL;   //メッシュインターフェース
	DWORD g_MaterialCount = 0;   //アテリアル数
	int *g_pTextureIds = NULL;   //テキスチャー管理番号保存用
	D3DMATERIAL9 *g_pMaterial = NULL;

	D3DXVECTOR3 position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 velocity = D3DXVECTOR3(0.0f,0.0f,0.0f);
	float rotation = 0.0f;
	ModelState nstate = DOWN;
	
};


bool LoadModel(LPDIRECT3DDEVICE9 pDevice, LPCTSTR modelFile, LPCSTR texturePath, Model &in_model);
void UninitModel(Model &in_model);
void DrawModel(LPDIRECT3DDEVICE9 pDevice, Model &in_model);
void UpdateModel(Model &in_model);
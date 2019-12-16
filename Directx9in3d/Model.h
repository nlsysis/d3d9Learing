#pragma once
#include "main.h"

struct Model
{
	LPD3DXMESH g_pMesh = NULL;   //���b�V���C���^�[�t�F�[�X
	DWORD g_MaterialCount = 0;   //�A�e���A����
	int *g_pTextureIds = NULL;   //�e�L�X�`���[�Ǘ��ԍ��ۑ��p
	D3DMATERIAL9 *g_pMaterial = NULL;	
};


bool LoadModel(LPDIRECT3DDEVICE9 pDevice, LPCTSTR modelFile, LPCSTR texturePath, Model &in_model);
void UninitModel(Model &in_model);
void DrawModel(LPDIRECT3DDEVICE9 pDevice, Model &in_model);
void UpdateModel(Model &in_model);
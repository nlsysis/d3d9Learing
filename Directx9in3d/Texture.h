#pragma once
#include "main.h"
int Texture_SetLoadFile(LPDIRECT3DDEVICE9 pDevice, char* fileName);
void Texture_Release(int textureId, DWORD materialCount);
LPDIRECT3DTEXTURE9 Texture_GetTexture(int textureId);
void LoadTexture(LPDIRECT3DDEVICE9 pDevice, LPCSTR fileName, LPDIRECT3DTEXTURE9 &texture);
void UninitTexture(LPDIRECT3DTEXTURE9 &texture);
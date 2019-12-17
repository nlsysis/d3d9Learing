#pragma once
#include "main.h"
#define EXPLOSSION_MAX 1000

struct EXPLOSSION
{
	D3DXVECTOR3 position;
	int nFrame;  //now frame
	int totalFrame;
	bool isUsed;
	int age;
};
void InitExplossion(LPDIRECT3DDEVICE9 pDevice, float sizeX, float sizeY);
void SetExplossion(D3DXVECTOR3 in_pos);
void DrawExplossion(LPDIRECT3DDEVICE9 pDevice);
void UninitExplossion();

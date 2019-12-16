#pragma once
#include "main.h"

#define BULLET_NUM 20

struct Bullet_tag
{
	bool isUsed;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 velocity;
};

void InitBullet(LPDIRECT3DDEVICE9 pDevice);
void UpdateBullet();
void DrawBullet(LPDIRECT3DDEVICE9 pDevice);
void UninitBullet();
void SetBullet(D3DXVECTOR3 position, D3DXVECTOR3 velocity);
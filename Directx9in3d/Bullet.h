#pragma once
#include "main.h"

#define BULLET_NUM 200

struct Bullet_tag
{
	bool isUsed;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 velocity;
	float radius;
};

void InitBullet(LPDIRECT3DDEVICE9 pDevice);
void UpdateBullet();
void DrawBullet(LPDIRECT3DDEVICE9 pDevice);
void UninitBullet();
void SetBullet(D3DXVECTOR3 position, D3DXVECTOR3 velocity);
bool IsBulletHitWall(const Bullet_tag &m_Bullet);
void SetBulletBoard(float width, float height);
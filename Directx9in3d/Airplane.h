#pragma once
#include "main.h"
#include "model.h"

enum AirplaneState { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

typedef struct Airplane_tag
{
	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	float velocity = 0.0f;
	AirplaneState nstate = DOWN;
	Model m_model;
	float radius = 0.0f;
};
void InitAirplane(LPDIRECT3DDEVICE9 pDevice);
void UpdateAirplane();
void DrawAirplane(LPDIRECT3DDEVICE9 pDevice);
void UninitAirplane();
D3DXVECTOR3 GetAirplanePos();
void SetBoard(float width, float height);
bool IsHitWall();
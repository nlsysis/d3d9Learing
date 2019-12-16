#pragma once
#include "main.h"
#include "model.h"

enum AirplaneState { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

typedef struct Airplane_tag
{
	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rotation = 0.0f;
	AirplaneState nstate = DOWN;
	Model m_model;
};
void InitAirplane(LPDIRECT3DDEVICE9 pDevice);
void UpdateAirplane();
void DrawAirplane(LPDIRECT3DDEVICE9 pDevice);
void UninitAirplane();
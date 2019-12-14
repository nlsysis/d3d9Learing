#pragma once
#include "main.h"

void InitCamera(LPDIRECT3DDEVICE9 p_device);

void UpdateCamera(LPDIRECT3DDEVICE9 p_device);

D3DXVECTOR3 GetCameraPosition();

D3DXMATRIX GetViewMatrix();
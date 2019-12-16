#pragma once
#include "main.h"

struct CAMERA_tag
{
	D3DXVECTOR3     pos;
	D3DXVECTOR3		at;
	D3DXVECTOR3		up;
	D3DXVECTOR3		rot;			// カメラの回転
	float		    len;			// カメラの視点と注視点の距離
	D3DXMATRIX		mtxView;
	D3DXMATRIX		mtxProjection;
};
void InitCameraFol(LPDIRECT3DDEVICE9 p_device);

void UpdateCameraFol(LPDIRECT3DDEVICE9 p_device);

D3DXVECTOR3 GetCameraFolPosition();

D3DXMATRIX GetFolViewMatrix();

void SetLookat(D3DXVECTOR3 atPos);
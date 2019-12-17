#pragma once
#include "main.h"
#define	CAM_IP_MAX			(2)
typedef struct CAMERA_tag
{
	D3DXVECTOR3     pos;
	D3DXVECTOR3		at;
	D3DXVECTOR3		up;
	D3DXVECTOR3		rot;			// カメラの回転
	float		    len;			// カメラの視点と注視点の距離
	D3DXMATRIX		mtxView;
	D3DXMATRIX		mtxProjection;
}CAMERA;

typedef struct
{
	bool				use;			// 使用しているかどうか
	float				move_time;		// 時間
	float				dt;				// １フレーム辺りの時間
	int					tbl_cnt;		// テーブルの要素数
	D3DXVECTOR3			*tbl;			// データテーブルのアドレス
} INTERPOLATION;

void InitCameraFol(LPDIRECT3DDEVICE9 p_device);

void UpdateCameraFol(LPDIRECT3DDEVICE9 p_device);

D3DXVECTOR3 GetCameraFolPosition();

D3DXMATRIX GetFolViewMatrix();

void SetLookat(D3DXVECTOR3 atPos);

CAMERA* GetCameraFol();

int GetIPCnt(void);
void UninitCameraFol();
#pragma once
#include "main.h"
#define	CAM_IP_MAX			(2)
typedef struct CAMERA_tag
{
	D3DXVECTOR3     pos;
	D3DXVECTOR3		at;
	D3DXVECTOR3		up;
	D3DXVECTOR3		rot;			// �J�����̉�]
	float		    len;			// �J�����̎��_�ƒ����_�̋���
	D3DXMATRIX		mtxView;
	D3DXMATRIX		mtxProjection;
}CAMERA;

typedef struct
{
	bool				use;			// �g�p���Ă��邩�ǂ���
	float				move_time;		// ����
	float				dt;				// �P�t���[���ӂ�̎���
	int					tbl_cnt;		// �e�[�u���̗v�f��
	D3DXVECTOR3			*tbl;			// �f�[�^�e�[�u���̃A�h���X
} INTERPOLATION;

void InitCameraFol(LPDIRECT3DDEVICE9 p_device);

void UpdateCameraFol(LPDIRECT3DDEVICE9 p_device);

D3DXVECTOR3 GetCameraFolPosition();

D3DXMATRIX GetFolViewMatrix();

void SetLookat(D3DXVECTOR3 atPos);

CAMERA* GetCameraFol();

int GetIPCnt(void);
void UninitCameraFol();
#include "camera.h"
#include "input.h"
#include "airplane.h"

D3DXVECTOR3 g_vecFront(0.0f, 0.0f, 1.0f);
D3DXVECTOR3 g_vecRight(1.0f, 0.0f, 0.0f);
D3DXVECTOR3 g_vecUp(0.0f, 1.0f, 0.0f);
D3DXVECTOR3 g_position(0.0f, 0.0f, 0.0f);  
D3DXVECTOR3 g_at;
D3DXVECTOR3 g_diff;  //the distance between camera to object
D3DXMATRIX matView;
D3DXMATRIX matProjection;
D3DXVECTOR3 g_rotation;
float  length = 1.0f;
float  g_Fov = 1.0f;   //大体60度
float  moveSpeed = 0.0f;    //移動速度
float  rotationSpeed = 0.0f;   //回転速度
bool  IsTargetObj;

void InitCamera(LPDIRECT3DDEVICE9 p_device)
{
	g_vecFront = D3DXVECTOR3(0.0f,-0.8f,1.0f);
	g_vecRight = D3DXVECTOR3(1.0f,0.0f,0.0f);
	D3DXVec3Cross(&g_vecUp, &g_vecFront, &g_vecRight);
	D3DXVec3Normalize(&g_vecFront,&g_vecFront);
	D3DXVec3Normalize(&g_vecUp, &g_vecUp);

	g_position = D3DXVECTOR3(0.0f, 40.0f, -120.0f);  // カメラの初期位置
	g_Fov = 1.0f;
	moveSpeed = 2.0f;
	rotationSpeed = D3DX_PI * 0.01f;

	D3DXMatrixPerspectiveFovLH(
		&matProjection,
		D3DX_PI / 4,   //ラジアン角で画角指定
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,
		0.1f,
		1000.0f);
	p_device->SetTransform(D3DTS_PROJECTION, &matProjection);

	g_at = GetAirplanePos();

	
	g_diff = g_at - g_position;
	length = sqrt(D3DXVec3Dot(&g_diff, &g_diff));
}


void UpdateCamera(LPDIRECT3DDEVICE9 p_device)
{
	D3DXVECTOR3 airplanePos = GetAirplanePos();
	rotationSpeed = D3DX_PI * 0.01f;
	D3DXVECTOR3 vecDir(0.0f,0.0f,0.0f);
	D3DXMATRIX mtxRotation;
	D3DXMatrixIdentity(&mtxRotation);
	g_at.x = airplanePos.x;
	g_at.z = airplanePos.z;
	Keyboard_Update();
	// 近づく
	if (Keyboard_IsPress(DIK_W))
	{
		vecDir += g_vecFront;
		//for move
		D3DXVec3Normalize(&vecDir, &vecDir);
		g_position += vecDir * moveSpeed;

		//normalize vector direction
		D3DXVec3Normalize(&g_vecFront, &g_vecFront);
		D3DXVec3Normalize(&g_vecRight, &g_vecRight);
		D3DXVec3Normalize(&g_vecUp, &g_vecUp);
		IsTargetObj = true;
	}
	// 離れる
	if (Keyboard_IsPress(DIK_S))
	{
		vecDir -= g_vecFront;
		//for move
		D3DXVec3Normalize(&vecDir, &vecDir);
		g_position += vecDir * moveSpeed;

		//normalize vector direction
		D3DXVec3Normalize(&g_vecFront, &g_vecFront);
		D3DXVec3Normalize(&g_vecRight, &g_vecRight);
		D3DXVec3Normalize(&g_vecUp, &g_vecUp);
		IsTargetObj = true;
	}

	//up and down
	if (Keyboard_IsPress(DIK_Q))
	{// 視点移動「上」
		vecDir += g_vecUp;
		//for move
		D3DXVec3Normalize(&vecDir, &vecDir);
		g_position += vecDir * moveSpeed;

		//normalize vector direction
		D3DXVec3Normalize(&g_vecFront, &g_vecFront);
		D3DXVec3Normalize(&g_vecRight, &g_vecRight);
		D3DXVec3Normalize(&g_vecUp, &g_vecUp);
	//	g_at = g_position + g_vecFront * length;
		IsTargetObj = false;
	}
	if (Keyboard_IsPress(DIK_E))
	{// 視点移動「下」
		vecDir -= g_vecUp;
		//for move
		D3DXVec3Normalize(&vecDir, &vecDir);
		g_position += vecDir * moveSpeed;

		//normalize vector direction
		D3DXVec3Normalize(&g_vecFront, &g_vecFront);
		D3DXVec3Normalize(&g_vecRight, &g_vecRight);
		D3DXVec3Normalize(&g_vecUp, &g_vecUp);
	//	g_at = g_position + g_vecFront * length;
		IsTargetObj = false;
	}

	if (Keyboard_IsPress(DIK_A))
	{// 注視点移動「上」
		g_at.y = airplanePos.y + moveSpeed;
		IsTargetObj = true;
	}
	if (Keyboard_IsPress(DIK_D))
	{// 注視点移動「上」
		g_at.y = airplanePos.y + moveSpeed;
		IsTargetObj = true;
	}
	////rotation in Up vector
	//if (Keyboard_IsPress(DIK_J))
	//{
	//	D3DXMatrixRotationAxis(&mtxRotation,&g_vecUp,rotationSpeed);
	//	//for rotation
	//	D3DXVec3TransformNormal(&g_vecFront, &g_vecFront, &mtxRotation);
	//	D3DXVec3TransformNormal(&g_vecRight, &g_vecRight, &mtxRotation);
	//}
	//if (Keyboard_IsPress(DIK_L))
	//{
	//	D3DXMatrixRotationAxis(&mtxRotation, &g_vecUp, -rotationSpeed);
	//	//for rotation
	//	D3DXVec3TransformNormal(&g_vecFront, &g_vecFront, &mtxRotation);
	//	D3DXVec3TransformNormal(&g_vecRight, &g_vecRight, &mtxRotation);
	//}
	//rotation in right vector
	//if (Keyboard_IsPress(DIK_I))
	//{
	//	g_rotation -= rotationSpeed;
	//	if (g_rotation > D3DX_PI / 8 || g_rotation < -D3DX_PI / 4)
	//	{
	//		g_rotation += rotationSpeed;
	//		rotationSpeed = 0.0f;
	//	}
	//	D3DXMatrixRotationAxis(&mtxRotation, &g_vecRight, -rotationSpeed);
	//	//for rotation
	//	D3DXVec3TransformNormal(&g_vecFront, &g_vecFront, &mtxRotation);
	//	D3DXVec3TransformNormal(&g_vecUp, &g_vecUp, &mtxRotation);
	//	
	//}
	//if (Keyboard_IsPress(DIK_K))
	//{
	//	g_rotation += rotationSpeed;
	//	if (g_rotation > D3DX_PI / 8 || g_rotation < -D3DX_PI / 4)
	//	{
	//		g_rotation -= rotationSpeed;
	//		rotationSpeed = 0.0f;
	//	}
	//	D3DXMatrixRotationAxis(&mtxRotation, &g_vecRight, rotationSpeed);
	//	//for rotation
	//	D3DXVec3TransformNormal(&g_vecFront, &g_vecFront, &mtxRotation);
	//	D3DXVec3TransformNormal(&g_vecUp, &g_vecUp, &mtxRotation);
	//	
	//	
	//}
	////rotation in forward vector
	//if (Keyboard_IsPress(DIK_F))
	//{
	//	D3DXMatrixRotationAxis(&mtxRotation, &g_vecFront, -rotationSpeed);
	//	//for rotation
	//	D3DXVec3TransformNormal(&g_vecRight, &g_vecRight, &mtxRotation);
	//	D3DXVec3TransformNormal(&g_vecUp, &g_vecUp, &mtxRotation);
	//}
	//if (Keyboard_IsPress(DIK_G))
	//{
	//	D3DXMatrixRotationAxis(&mtxRotation, &g_vecFront, rotationSpeed);
	//	//for rotation
	//	D3DXVec3TransformNormal(&g_vecRight, &g_vecRight, &mtxRotation);
	//	D3DXVec3TransformNormal(&g_vecUp, &g_vecUp, &mtxRotation);
	//}
	//if (Keyboard_IsTrigger(DIK_SPACE))
	//{
	//	IsTargetObj = (IsTargetObj == true ? false : true);
	//}
	////normalize vector direction
	//D3DXVec3Normalize(&g_vecFront, &g_vecFront);
	//D3DXVec3Normalize(&g_vecRight, &g_vecRight);
	//D3DXVec3Normalize(&g_vecUp, &g_vecUp);
	

	g_diff = g_at - g_position;
	length = sqrt(D3DXVec3Dot(&g_diff, &g_diff));

	
	D3DXMatrixLookAtLH(&matView, &g_position, &g_at, &g_vecUp);
	p_device->SetTransform(D3DTS_VIEW, &matView);
	p_device->SetRenderState(D3DRS_LIGHTING, false);
	if (IsTargetObj)
	{
		//rotation the camera round an obj
		g_position = g_at - g_vecFront * length;
	}
	else
	{
		g_at = g_position + g_vecFront * length;
	}
	//matWorld = matRotation * matTranslation;
	//p_device->SetTransform(D3DTS_WORLD, &matWorld); //デバイスにワールド変換行列を設定
}

D3DXVECTOR3 GetCameraPosition()
{
	return g_position;
}

D3DXMATRIX GetViewMatrix()
{
	return matView;
}
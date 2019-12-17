#include "Airplane.h"
#include "input.h"
#include "bullet.h"
#include <vector>
#include "cameraFol.h"
#include <algorithm>
#include "shadow.h"
/**
 グローバル変数
**/
float dt = 0.05f;
float speed = 2.0f;
float rotationRadian = 0.2f;
Airplane_tag m_airplane;
float airplaneWidth = 10.0f;
float m_boardW = 0.0f;
float m_boardH = 0.0f;
ShadowType airplaneShadow;
bool startSpin = false, finishSpin = true;
int prevDir = 1;
float targetRad = 0.0f, spinRad = 0.0f, tmpRad = 0.0f;

void InitAirplane(LPDIRECT3DDEVICE9 pDevice)
{
	LoadModel(pDevice, ".\\Resource\\airplane000.x", NULL, m_airplane.m_model);
	m_airplane.radius = 8.0f;
	m_airplane.position.y = 3.0f;
	InitBullet(pDevice);
	InitShadow(pDevice,10.0f,10.0f, airplaneShadow);
}
void UpdateAirplane()
{
	CAMERA * g_camera = GetCameraFol();
	bool isKey = false;

	int dir = 0;
	if (Keyboard_IsPress(DIK_LEFT))
	{
		dir |= 8;
		m_airplane.velocity = speed;
		isKey = true;
	}
	if (Keyboard_IsPress(DIK_RIGHT))
	{
		dir |= 4;
		m_airplane.velocity = speed;
		isKey = true;
	}
	if (Keyboard_IsPress(DIK_UP))
	{
		dir |= 2;
	    m_airplane.velocity = speed;
		isKey = true;
	}
	if (Keyboard_IsPress(DIK_DOWN))
	{
		dir |= 1;
		m_airplane.velocity = speed;
		isKey = true;
	}

	if (Keyboard_IsPress(DIK_R))
	{
		m_airplane.position.z = m_airplane.position.x = 0.0f;
		dir = 1;
		m_airplane.velocity = 0.0f;
		isKey = true;
	}
	if (Keyboard_IsPress(DIK_LSHIFT))
	{
		m_airplane.rotation.y += rotationRadian;
		isKey = true;
	}
	if (Keyboard_IsPress(DIK_RSHIFT))
	{
		m_airplane.rotation.y -= rotationRadian;
		isKey = true;
	}
	// 入力されたキーに合わせて向きを決める
	float roty = 0.0f;
	if (finishSpin) {
		switch (dir)
		{
		case 1:	// 下向き
			roty = 0.0f;
			startSpin = true;
			finishSpin = false;
			break;

		case 2:	// 上向き
			roty = D3DX_PI;
			startSpin = true;
			finishSpin = false;
			break;

		case 4:	// 右向き
			roty = -D3DX_PI / 2;
			startSpin = true;
			finishSpin = false;
			break;

		case 8:	// 左向き
			roty = D3DX_PI / 2;
			startSpin = true;
			finishSpin = false;
			break;

		case 5:	// 右下向き
			roty = -D3DX_PI / 4;
			startSpin = true;
			finishSpin = false;
			break;

		case 6:	// 右上向き
			roty = -D3DX_PI / 4 * 3;
			startSpin = true;
			finishSpin = false;
			break;

		case 9:	// 左下向き
			roty = D3DX_PI / 4;
			startSpin = true;
			finishSpin = false;
			break;

		case 10: // 左上向き
			roty = D3DX_PI / 4 * 3;
			startSpin = true;
			finishSpin = false;
			break;

			//case 0:
			//	roty =m_airplane.rotation.y - g_camera->rot.y;
			//	break;

		}
	}

	if (dir == 0)
	{
		roty = m_airplane.rotation.y - g_camera->rot.y;
	}
	

	

	if (startSpin && !finishSpin) {
		int tmpDir = log2(dir) + 1;
		switch (tmpDir)
		{
		case 1:  // 下向き パターンを押し
			targetRad = 0;
			break;
		case 2: // 上向き パターンを押し
			targetRad = D3DX_PI;
			break;
		case 3:
			targetRad = -D3DX_PI / 2;
			break;
		case 4:
			targetRad = D3DX_PI / 2;
			break;
		}

		int tmpDir2 = log2(prevDir) + 1;
		switch (tmpDir2)
		{
		case 1:
			tmpRad = 0;
			break;
		case 2:
			tmpRad = D3DX_PI;
			break;
		case 3:
			tmpRad = -D3DX_PI / 2;
			break;
		case 4:
			tmpRad = D3DX_PI / 2;
			break;
		}

		prevDir = dir;

		startSpin = false;
	}

	if (abs(targetRad - tmpRad) > 0.005f) {
		if (abs(targetRad - tmpRad) >= D3DX_PI) {
			if (targetRad > tmpRad)
				targetRad = tmpRad - D3DX_PI / 2;
			else
				targetRad = tmpRad + D3DX_PI / 2;
		}
		else {
			if (targetRad > tmpRad)
				tmpRad += D3DX_PI / 16;
			else
				tmpRad -= D3DX_PI / 16;
		}

		roty = tmpRad;
	}
	else {
		finishSpin = true;
	}


	// Key入力があったら移動処理する
	//if(isKey)
	{
		// カメラに対して入力のあった方向へプレイヤーを向かせて移動させる
		m_airplane.rotation.y = roty + g_camera->rot.y;
		if (IsHitWall())
		{
			m_airplane.velocity = 0.0f;
		}
		m_airplane.position.x -= sinf(m_airplane.rotation.y) * m_airplane.velocity;
		m_airplane.position.z -= cosf(m_airplane.rotation.y) * m_airplane.velocity;

		
		// カメラの注視点と視点を主人公に追従させる
		if (GetIPCnt() == 0)
		{
			g_camera->at.x = m_airplane.position.x;
			g_camera->at.z = m_airplane.position.z;
			g_camera->pos.x = g_camera->at.x - sinf(g_camera->rot.y) * g_camera->len;
			g_camera->pos.z = g_camera->at.z - cosf(g_camera->rot.y) * g_camera->len;
		}
	}
	

	// Keyを話した時に少し慣性っぽくする
	m_airplane.velocity *= 0.9f;

	m_airplane.position.x = (std::min)(m_airplane.position.x, 310.0f);
	m_airplane.position.x = (std::max)(m_airplane.position.x, -310.0f);
	m_airplane.position.z = (std::min)(m_airplane.position.z, 310.0f);
	m_airplane.position.z = (std::max)(m_airplane.position.z, -310.0f);

	
	if (Keyboard_IsTrigger(DIK_SPACE))
	{
		
		SetBullet(m_airplane.position,
			D3DXVECTOR3(-sinf(m_airplane.rotation.y) * (m_airplane.velocity + 1.0f), 0.0f, -cosf(m_airplane.rotation.y) * (m_airplane.velocity +1.0f)));
	}
	
}
void DrawAirplane(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXMATRIX matWorld, matTrans, matRoll;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationYawPitchRoll(&matRoll, m_airplane.rotation.y, m_airplane.rotation.x, m_airplane.rotation.z);
	D3DXMatrixTranslation(&matTrans, m_airplane.position.x, m_airplane.position.y, m_airplane.position.z);
	matWorld = matWorld * matRoll  * matTrans;
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	DrawModel(pDevice,m_airplane.m_model);

	DrawBullet(pDevice);

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matTrans, m_airplane.position.x, 0.1f, m_airplane.position.z);
	matWorld = matWorld  * matTrans;
	DrawShadow(pDevice, matWorld, airplaneShadow);
}
void UninitAirplane()
{
	UninitModel(m_airplane.m_model);
	UninitBullet();
	UninitShadow(airplaneShadow);
}

D3DXVECTOR3 GetAirplanePos()
{
	return m_airplane.position;
}

void SetBoard(float width,float height)
{
	m_boardW = width;
	m_boardH = height;
	SetBulletBoard(width, height);
}
bool IsHitWall()
{
	D3DXVECTOR3 pos;
	pos.x= m_airplane.position.x-sinf(m_airplane.rotation.y) * m_airplane.velocity;
	pos.z= m_airplane.position.z - cosf(m_airplane.rotation.y) * m_airplane.velocity;
	if (pos.x + m_airplane.radius >= m_boardW || pos.x - m_airplane.radius <= -m_boardW) return true;
	if (pos.z + m_airplane.radius >= m_boardH || pos.z - m_airplane.radius <= -m_boardH) return true;
	return false;
}
#include "Airplane.h"
#include "input.h"
#include "bullet.h"
#include <vector>

/**
 ƒOƒ[ƒoƒ‹•Ï”
**/
float dt = 0.05f;
float speed = 1.0f;
Airplane_tag m_airplane;

void InitAirplane(LPDIRECT3DDEVICE9 pDevice)
{
	LoadModel(pDevice, ".\\Resource\\airplane000.x", NULL, m_airplane.m_model);

	InitBullet(pDevice);
}
void UpdateAirplane()
{
	if (Keyboard_IsPress(DIK_UP))
	{
		//rotation
		switch (m_airplane.nstate)
		{
		case UP:
			break;
		case DOWN:
			m_airplane.rotation += D3DX_PI;
			break;
		case LEFT:
			m_airplane.rotation += D3DX_PI / 2;
			break;
		case RIGHT:
			m_airplane.rotation += -D3DX_PI / 2;
			break;
		}
		m_airplane.velocity.x += sin(m_airplane.rotation) * speed;
		m_airplane.velocity.z += -cos(m_airplane.rotation) * speed;
		m_airplane.nstate = UP;
	}
	if (Keyboard_IsPress(DIK_DOWN))
	{
		switch (m_airplane.nstate)
		{
		case UP:
			m_airplane.rotation += D3DX_PI;
			break;
		case DOWN:
			break;
		case LEFT:
			m_airplane.rotation += -D3DX_PI / 2;
			break;
		case RIGHT:
			m_airplane.rotation += D3DX_PI / 2;
			break;
		}
		m_airplane.velocity.x += sin(m_airplane.rotation) * speed;
		m_airplane.velocity.z += -cos(m_airplane.rotation) * speed;
	//	m_airplane.velocity.z -= 1.0f;
		m_airplane.nstate = DOWN;
	}
	if (Keyboard_IsPress(DIK_LEFT))
	{
		switch (m_airplane.nstate)
		{
		case UP:
			m_airplane.rotation += -D3DX_PI / 2;
			break;
		case DOWN:
			m_airplane.rotation += D3DX_PI / 2;
			break;
		case LEFT:
			break;
		case RIGHT:
			m_airplane.rotation += D3DX_PI;
			break;
		}
		m_airplane.velocity.x += -sin(m_airplane.rotation) * speed;
		m_airplane.velocity.z += -cos(m_airplane.rotation) * speed;
	//	m_airplane.velocity.x -= 1.0f;
		m_airplane.nstate = LEFT;
	}
	if (Keyboard_IsPress(DIK_RIGHT))
	{
		switch (m_airplane.nstate)
		{
		case UP:
			m_airplane.rotation += D3DX_PI / 2;
			break;
		case DOWN:
			m_airplane.rotation += -D3DX_PI / 2;
			break;
		case LEFT:
			m_airplane.rotation += D3DX_PI;
			break;
		case RIGHT:
			break;
		}
		m_airplane.velocity.x += -sin(m_airplane.rotation) * speed;
		m_airplane.velocity.z += -cos(m_airplane.rotation) * speed;
	//	m_airplane.velocity.x += 1.0f;
		m_airplane.nstate = RIGHT;
	}
	//set Bullet
	if (Keyboard_IsTrigger(DIK_SPACE))
	{
		SetBullet(m_airplane.position,D3DXVECTOR3(0.0f,0.0f,1.0f * dt));
	}
	if (abs(m_airplane.velocity.x) > 0.1)
	{
		m_airplane.velocity.x -= m_airplane.velocity.x * 0.1f;
	}
	else m_airplane.velocity.x = 0.0f;
	if (abs(m_airplane.velocity.y) > 0.1)
	{
		m_airplane.velocity.y -= m_airplane.velocity.y * 0.1f;
	}
	else m_airplane.velocity.y = 0.0f;
	if (abs(m_airplane.velocity.z) > 0.1)
	{
		m_airplane.velocity.z -= m_airplane.velocity.z * 0.1f;
	}
	else m_airplane.velocity.z = 0.0f;
	m_airplane.position += m_airplane.velocity * dt;
}
void DrawAirplane(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXMATRIX matWorld, matScale, matTrans, matRoll, matTrans2;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	D3DXMatrixRotationY(&matRoll, m_airplane.rotation);
	D3DXMatrixTranslation(&matTrans, m_airplane.position.x, m_airplane.position.y, m_airplane.position.z);
	matWorld = matWorld * matRoll * matScale * matTrans;
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	DrawModel(pDevice,m_airplane.m_model);

	DrawBullet(pDevice);
}
void UninitAirplane()
{
	UninitModel(m_airplane.m_model);
}
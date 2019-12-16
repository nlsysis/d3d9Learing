#include "Airplane.h"
#include "input.h"
#include "bullet.h"
#include <vector>
/**
 ÉOÉçÅ[ÉoÉãïœêî
**/
float dt = 0.05f;
float speed = 0.5f;
float rotationRadian = 0.5f;
Airplane_tag m_airplane;
float airplaneWidth = 10.0f;


void InitAirplane(LPDIRECT3DDEVICE9 pDevice)
{
	LoadModel(pDevice, ".\\Resource\\airplane000.x", NULL, m_airplane.m_model);

	InitBullet(pDevice);
}
void UpdateAirplane()
{
	if (Keyboard_IsPress(DIK_W))
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
	if (Keyboard_IsPress(DIK_S))
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
	if (Keyboard_IsPress(DIK_A))
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
	if (Keyboard_IsPress(DIK_D))
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
		float bullet_speedX = 0.0f;
		float bullet_speedZ = 0.0f;
		D3DXVECTOR3 pos = m_airplane.position;
		switch (m_airplane.nstate)
		{
		case UP:
			pos.z += airplaneWidth;
			break;
		case DOWN:
			pos.z -= airplaneWidth;
			break;
		case LEFT:
			pos.x -= airplaneWidth;
			break;
		case RIGHT:
			pos.x += airplaneWidth;
			break;
		}
		bullet_speedX = -sin(m_airplane.rotation);
		bullet_speedZ = -cos(m_airplane.rotation);
		if (abs(bullet_speedX) < 0.1f)
		{
			bullet_speedX = 0;
		}
		if (abs(bullet_speedZ) < 0.1f)
		{
			bullet_speedZ = 0;
		}
		SetBullet(pos, D3DXVECTOR3(bullet_speedX * 0.75f, 0.0f, bullet_speedZ * 0.75f));
	}
	if (Keyboard_IsPress(DIK_Z))
	{
		m_airplane.position.y += 1.0f;
	}
	if (Keyboard_IsPress(DIK_M))
	{
		m_airplane.position.y -= 1.0f;
	}
	if (Keyboard_IsPress(DIK_LSHIFT))
	{
		m_airplane.rotation += D3DX_PI / 60;
	}

	if (Keyboard_IsPress(DIK_RSHIFT))
	{
		m_airplane.rotation -= D3DX_PI / 60;
	}



	if (m_airplane.position.y < 0.0f)
	{
		m_airplane.position.y = 0.0f;
	}
	if (abs(m_airplane.velocity.x) > 0.1)
	{
		m_airplane.velocity.x -= m_airplane.velocity.x * 0.07f;
	}
	else m_airplane.velocity.x = 0.0f;
	if (abs(m_airplane.velocity.y) > 0.1)
	{
		m_airplane.velocity.y -= m_airplane.velocity.y * 0.07f;
	}
	else m_airplane.velocity.y = 0.0f;
	if (abs(m_airplane.velocity.z) > 0.1)
	{
		m_airplane.velocity.z -= m_airplane.velocity.z * 0.07f;
	}
	else m_airplane.velocity.z = 0.0f;
	m_airplane.position += m_airplane.velocity ;
	
}
void DrawAirplane(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXMATRIX matWorld, matTrans, matRoll;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationY(&matRoll, m_airplane.rotation);
	D3DXMatrixTranslation(&matTrans, m_airplane.position.x, m_airplane.position.y, m_airplane.position.z);
	matWorld = matWorld * matRoll  * matTrans;
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	DrawModel(pDevice,m_airplane.m_model);

	DrawBullet(pDevice);
}
void UninitAirplane()
{
	UninitModel(m_airplane.m_model);
	UninitBullet();
}

D3DXVECTOR3 GetAirplanePos()
{
	return m_airplane.position;
}
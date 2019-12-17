#include "Bullet.h"
#include "Billboard.h"
#include "texture.h"
#include "shadow.h"
#include "explostionEffect.h"

Bullet_tag m_Bullet[BULLET_NUM];
LPDIRECT3DTEXTURE9 bulletTexture = nullptr;
float boardW = 0.0f;
float boardH = 0.0f;
ShadowType bulletShadow;

void InitBullet(LPDIRECT3DDEVICE9 pDevice)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		m_Bullet[i].isUsed= false;
		m_Bullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Bullet[i].velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Bullet[i].radius = 1.8f;
	}
	LoadTexture(pDevice, ".\\Resource\\texture\\bullet000.png", bulletTexture);

	InitBillboard(pDevice, 3.0f, 3.0f);
	InitShadow(pDevice, 3.0f,  3.0f, bulletShadow);
	InitExplossion(pDevice,3.0f,3.0f);
}
void UpdateBullet()
{

}
void DrawBullet(LPDIRECT3DDEVICE9 pDevice)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (m_Bullet[i].isUsed)
		{
			m_Bullet[i].pos += m_Bullet[i].velocity;
			if (IsBulletHitWall(m_Bullet[i]))
			{
				//effect
				SetExplossion(m_Bullet[i].pos);
				m_Bullet[i].isUsed = false;
				continue;
			}
			D3DXMATRIX matWorld,  matTrans, matRoll, matTrans2;
			//shadow
			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixTranslation(&matTrans, m_Bullet[i].pos.x, 0.2f, m_Bullet[i].pos.z);
			matWorld = matWorld * matTrans;
			DrawShadow(pDevice, matWorld, bulletShadow);

			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixTranslation(&matTrans, m_Bullet[i].pos.x, m_Bullet[i].pos.y + 3.0f, m_Bullet[i].pos.z);
			matWorld = matWorld * matTrans;
			DrawBillboard(pDevice, bulletTexture, matWorld);
		}
	}
	DrawExplossion(pDevice);
}
void UninitBullet()
{
	UninitTexture(bulletTexture);
	UninitBillboard();
	UninitShadow(bulletShadow);
	UninitExplossion();
}


void SetBullet(D3DXVECTOR3 position,D3DXVECTOR3 velocity)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (m_Bullet[i].isUsed) continue;
		m_Bullet[i].isUsed = true;
		m_Bullet[i].pos = position;
		m_Bullet[i].velocity = velocity;
		break;
	}
}

void SetBulletBoard(float width, float height)
{
	boardW = width;
	boardH = height;
}

bool IsBulletHitWall(const Bullet_tag &m_Bullet)
{
	if (m_Bullet.pos.x + m_Bullet.radius >= boardW || m_Bullet.pos.x - m_Bullet.radius <= -boardW) return true;
	if (m_Bullet.pos.z + m_Bullet.radius >= boardH || m_Bullet.pos.z - m_Bullet.radius <= -boardH) return true;
	return false;
}
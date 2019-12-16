#include "Bullet.h"
#include "Billboard.h"
#include "texture.h"
#include "shadow.h"

Bullet_tag m_Bullet[BULLET_NUM];
LPDIRECT3DTEXTURE9 bulletTexture = nullptr;

void InitBullet(LPDIRECT3DDEVICE9 pDevice)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		m_Bullet[i].isUsed= false;
		m_Bullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Bullet[i].velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	LoadTexture(pDevice, ".\\Resource\\texture\\bullet000.png", bulletTexture);

	InitBillboard(pDevice,0.5f,0.5f);
	InitShadow(pDevice, 0.5f, 0.5f);
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
			D3DXMATRIX matWorld,  matTrans, matRoll, matTrans2;
			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixTranslation(&matTrans, m_Bullet[i].pos.x, m_Bullet[i].pos.y + 0.6f,m_Bullet[i].pos.z);
			matWorld = matWorld * matTrans;
			DrawBillboard(pDevice, bulletTexture, matWorld);
			//shadow
			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixTranslation(&matTrans, m_Bullet[i].pos.x, 0.1f, m_Bullet[i].pos.z);
			matWorld = matWorld * matTrans;
			DrawShadow(pDevice, matWorld);
		}
	}
}
void UninitBullet()
{
	UninitTexture(bulletTexture);
	UninitBillboard();
	UninitShadow();
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
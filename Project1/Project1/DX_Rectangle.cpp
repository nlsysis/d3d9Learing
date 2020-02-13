#include "DX_Rectangle.h"

DX_Rectangle::DX_Rectangle()
{

}
DX_Rectangle::~DX_Rectangle()
{
}

void DX_Rectangle::InitRectangleBK(Vertex2d rect, float height, float width)
{
	m_Rectangle[1] = rect;
	m_length = height;
	m_width = width;
	m_Rectangle[0] = { D3DXVECTOR4(m_Rectangle[1].position.x,
			m_Rectangle[1].position.y + m_length,0.0f,1.0f),D3DCOLOR_RGBA(30,144,255,255)};
	m_Rectangle[2] = { D3DXVECTOR4(m_Rectangle[1].position.x + m_width,
			m_Rectangle[1].position.y + m_length,0.0f,1.0f),D3DCOLOR_RGBA(30,144,255,255)};
	m_Rectangle[3] = { D3DXVECTOR4(m_Rectangle[1].position.x + m_width,
			m_Rectangle[1].position.y,0.0f,1.0f),rect.color };
}

void DX_Rectangle::InitRectangle(Vertex2d rect, float height, float width)
{
	m_Rectangle[1] = rect;
	m_length = height;
	m_width = width;
	m_Rectangle[0] = { D3DXVECTOR4(m_Rectangle[1].position.x,
			m_Rectangle[1].position.y + m_length,0.0f,1.0f),rect.color };
	m_Rectangle[2] = { D3DXVECTOR4(m_Rectangle[1].position.x + m_width,
			m_Rectangle[1].position.y + m_length,0.0f,1.0f),rect.color };
	m_Rectangle[3] = { D3DXVECTOR4(m_Rectangle[1].position.x + m_width,
			m_Rectangle[1].position.y,0.0f,1.0f),rect.color };
}

D3DXVECTOR4 DX_Rectangle::GetCenter()
{
	m_center = { 0.0f, 0.0f,0.0f,0.0f };
	for (int i = 0; i < 4; i++)
	{
		m_center += m_Rectangle[i].position;
	}
	return m_center/4;
}
void DX_Rectangle::TranslationRectangle(D3DXVECTOR3 trans)
{
	for (int i = 0; i < 4; i++)
	{
		m_Rectangle[i].position.x += trans.x;
		m_Rectangle[i].position.y += trans.y;
		m_Rectangle[i].position.z += trans.z;

	}
}
void DX_Rectangle::ChangeRectangleColor(D3DCOLOR color)
{
	for (int i = 0; i < 4; i++)
	{
		m_Rectangle[i].color = color;

	}
}
void DX_Rectangle::RotationRectangle(float degree)
{
	D3DXVECTOR4 temp;
	D3DXVECTOR4 g_center = GetCenter();
	for (int i = 0; i < 4; i++)
	{
		temp = m_Rectangle[i].position - g_center;
		m_Rectangle[i].position.x = temp.x * cos(D3DXToRadian(degree)) - temp.y * sin(D3DXToRadian(degree)) + g_center.x;
		m_Rectangle[i].position.y = temp.x * sin(D3DXToRadian(degree)) + temp.y * cos(D3DXToRadian(degree)) + g_center.y;
		//v_Triangle[i].position.z = trans.z;
	}
}
void DX_Rectangle::ScaleRectangle(D3DXVECTOR3 sizePresent)
{
	for (int i = 0; i < 4; i++)
	{
		m_Rectangle[i].position.x *= sizePresent.x;
		m_Rectangle[i].position.y *= sizePresent.y;
		m_Rectangle[i].position.z *= sizePresent.z;

	}
}
void DX_Rectangle::DrawRectangle(LPDIRECT3DDEVICE9 device)
{
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_Rectangle, sizeof(Vertex2d));
	//device->DrawPrimitiveUP(D3DPT_LINESTRIP, 3, m_Rectangle, sizeof(Vertex2d));
}

void DX_Rectangle::ChangeRectangleByWidth(float width)
{
	m_Rectangle[2].position.x += width;
	m_Rectangle[3].position.x += width;
}
void DX_Rectangle::ChangeRectangleByLWidth(float width)
{
	m_Rectangle[0].position.x += width;
	m_Rectangle[1].position.x += width;
}
void DX_Rectangle::ChangeRectangleByLength(float length)
{
	m_Rectangle[0].position.y += length;
	m_Rectangle[2].position.y += length;
}

void DX_Rectangle::RotationRectangleY(float degree)
{
	D3DXVECTOR4 temp;
	D3DXVECTOR4 g_center = GetCenter();
	for (int i = 0; i < 4; i++)
	{
		temp = m_Rectangle[i].position - g_center;
		m_Rectangle[i].position.x = temp.x * cos(D3DXToRadian(degree)) - temp.z * sin(D3DXToRadian(degree)) + g_center.x;
		m_Rectangle[i].position.z = temp.x * sin(D3DXToRadian(degree)) + temp.z * cos(D3DXToRadian(degree)) + g_center.y;
		//v_Triangle[i].position.z = trans.z;
	}
}

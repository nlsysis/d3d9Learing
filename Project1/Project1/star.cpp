#include "star.h"

Star::Star()
{

}

Star::~Star()
{
}

void Star::InitStar(Vertex2d center, float br, float ir,int flag)
{
	if (flag == 0)
	{
		m_Star[0] = center;
		int No = 0;
		for (int i = 1; i < 12; )
		{
			m_Star[i].position.x = br * cos(2 * D3DX_PI * No / 5);
			m_Star[i].position.y = br * sin(2 * D3DX_PI * No / 5);
			m_Star[i].color = D3DCOLOR_RGBA(255, 255, 0, 255);
			m_Star[i].position += center.position;

			m_Star[i + 1].position.x = ir * cos(2 * D3DX_PI * No / 5 + D3DX_PI / 5);
			m_Star[i + 1].position.y = ir * sin(2 * D3DX_PI * No / 5 + D3DX_PI / 5);
			m_Star[i+1].color = D3DCOLOR_RGBA(255, 255, 0, 255);
			m_Star[i + 1].position += center.position;

			m_Star[1].color = D3DCOLOR_RGBA(255, 255, 0, 255);
			i += 2;
			No++;
		}
	}
	
	else if (flag == 1)
	{
		m_Star[0] = center;
		int No = 0;
		for (int i = 1; i < 12; )
		{
			m_Star[i].position.x = br * cos(2 * D3DX_PI * No / 5);
			m_Star[i].position.y = br * sin(2 * D3DX_PI * No / 5);
			m_Star[i].color = D3DCOLOR_RGBA(255, 255, 0, 255);
			m_Star[i].position += center.position;

			m_Star[i + 1].position.x = ir * cos(2 * D3DX_PI * No / 5);
			m_Star[i + 1].position.y = ir * sin(2 * D3DX_PI * No / 5);
			m_Star[i + 1].color = D3DCOLOR_RGBA(255, 255, 0, 255);
			m_Star[i + 1].position += center.position;

			i += 2;
			No++;
		}		
	}

}
void Star::TranslationStar(D3DXVECTOR4 trans)
{
	for (int i = 0; i < 12; i++)
	{
		m_Star[i].position += trans;
	}
}
void Star::RotationStar(float degree)
{
	D3DXVECTOR4 m_center = m_Star[0].position;
	for (int i = 0; i < 12; i++)
	{
		D3DXVECTOR4 temp = m_Star[i].position - m_center;
		m_Star[i].position.x = temp.x * cos(D3DXToRadian(degree)) - temp.y * sin(D3DXToRadian(degree))+ m_center.x;
		m_Star[i].position.y = temp.y * cos(D3DXToRadian(degree)) + temp.x * sin(D3DXToRadian(degree)) + m_center.y;
		//m_Star[i].position += m_center;
	}
}
void Star::ScaleStar(D3DXVECTOR3 sizePresent)
{
	for (int i = 0; i < 12; i++)
	{
		D3DXVECTOR4 temp = m_Star[i].position - m_Star[0].position;
		temp.x *= sizePresent.x;
		temp.y *= sizePresent.y;
		temp.z *= sizePresent.z;

		m_Star[i].position = temp + m_Star[0].position;
	}
}

void Star::DrawStar(LPDIRECT3DDEVICE9 device)
{
	device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 10, m_Star, sizeof(Vertex2d));
	//device->DrawPrimitiveUP(D3DPT_LINESTRIP, 10, m_Star, sizeof(Vertex2d));
}

Vertex2d Star::GetStarCenter()
{
	return m_Star[0];
}

void Star::RotationStarByPoint(Position point, float degree)
{
	D3DXVECTOR4 m_center;
	m_center.x =  point.x;
	m_center.y = point.y;
	m_center.z = 0.0f;
	m_center.w = 0.0f;
	for (int i = 0; i < 12; i++)
	{
		D3DXVECTOR4 temp = m_Star[i].position - m_center;
		m_Star[i].position.x = temp.x * cos(D3DXToRadian(degree)) - temp.y * sin(D3DXToRadian(degree)) + m_center.x;
		m_Star[i].position.y = temp.y * cos(D3DXToRadian(degree)) + temp.x * sin(D3DXToRadian(degree)) + m_center.y;
		//m_Star[i].position += m_center;
	}
}

void Star::ChangeColor(D3DCOLOR color)
{
	for (int i = 0; i < 12; i++)
	{
		m_Star[i].color = color;
	}
}
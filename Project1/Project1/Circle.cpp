#include "Circle.h"

Circle::Circle()
{
}
Circle::~Circle()
{
}
void Circle::InitCircle(Vertex2d center,float radius,int pointCount)
{
	m_center = center.position;
	m_radius = radius;
	m_pointCount = pointCount;
	m_Circle = new Vertex2d[m_pointCount];
	m_Circle[0] = center;
	for (int i = 1; i < m_pointCount; i++)
	{
		m_Circle[i].position.x = m_radius * cos( 2 * D3DX_PI / (m_pointCount - 2) * i);
		m_Circle[i].position.y = m_radius * sin( 2 * D3DX_PI / (m_pointCount - 2) * i);
		m_Circle[i].position.z = 0;
		m_Circle[i].color = center.color;
		/*if (m_Circle[i].position.x < 0)
		{
			m_Circle[i].color = center.color * 0.5;
		}*/
		m_Circle[i].position += m_center;
		
	}
}
D3DXVECTOR4  Circle::GetCenter()
{
	return m_Circle[0].position;
}
void Circle::TranslationCircle(D3DXVECTOR4 trans)
{
	for (int i = 0; i < m_pointCount; i++)
	{
		m_Circle[i].position += trans;
	}
}
void Circle::RotationCircle(float degree)
{
	for (int i = 0; i < m_pointCount; i++)
	{
		D3DXVECTOR4 temp = m_Circle[i].position - m_center;
		m_Circle[i].position.x = temp.x * cos(D3DXToRadian(degree)) - temp.y * sin(D3DXToRadian(degree));
		m_Circle[i].position.y = temp.y * cos(D3DXToRadian(degree)) + temp.x * sin(D3DXToRadian(degree));
		m_Circle[i].position += m_center;
	}
}
//void ScaleCircle(D3DXVECTOR3 sizePresent);
void Circle::DrawCircle(LPDIRECT3DDEVICE9 device)
{
	device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, m_pointCount - 2, m_Circle, sizeof(Vertex2d));
}
#include "hook.h"
//
//Hook::Hook()
//{
//}
//Hook::~Hook()
//{
//}
//void Hook::InitHook(Vertex2d center, float radius, int pointCount)
//{
//	Vertex2d *m_Circle;
//	Vertex2d *m_Circle2;
//	m_center = center.position;
//	m_radius = radius;
//	m_pointCount = pointCount;
//	m_Circle = new Vertex2d[m_pointCount/2];
//	//m_Circle[0] = center;
//	for (int i = 0; i < m_pointCount/2; i++)
//	{
//		m_Circle[i].position.x = m_radius * cos(2 * D3DX_PI / pointCount * (i) + D3DX_PI / 2);
//		m_Circle[i].position.y = m_radius * sin(2 * D3DX_PI / pointCount * (i) + D3DX_PI / 2);
//		m_Circle[i].position.z = 0;
//		m_Circle[i].color = center.color;
//		/*if (m_Circle[i].position.x < 0)
//		{
//			m_Circle[i].color = center.color * 0.5;
//		}*/
//		m_Circle[i].position += m_center;
//
//	}
//	m_Circle2 = new Vertex2d[m_pointCount/2];
//	for (int i = 0; i < m_pointCount/2; i++)
//	{
//		m_Circle2[i].position.x = (m_radius + 6) * cos(2 * D3DX_PI / pointCount * (i)+D3DX_PI / 2);
//		m_Circle2[i].position.y = (m_radius + 6) * sin(2 * D3DX_PI / pointCount * (i)+D3DX_PI / 2);
//		m_Circle2[i].position.z = 0;
//		m_Circle2[i].color = center.color;
//		m_Circle2[i].position += m_center;
//	}
//	g_Circle = new Vertex2d[pointCount];
//
//}
//D3DXVECTOR4  Hook::GetCenter()
//{
//	return g_Circle[0].position;
//}
//void Hook::TranslationHook(D3DXVECTOR4 trans)
//{
//	for (int i = 0; i < m_pointCount; i++)
//	{
//		g_Circle[i].position += trans;
//	}
//}
//void Hook::RotationHook(float degree)
//{
//	for (int i = 0; i < m_pointCount; i++)
//	{
//		D3DXVECTOR4 temp = m_Circle[i].position - m_center;
//		g_Circle[i].position.x = temp.x * cos(D3DXToRadian(degree)) - temp.y * sin(D3DXToRadian(degree));
//		g_Circle[i].position.y = temp.y * cos(D3DXToRadian(degree)) + temp.x * sin(D3DXToRadian(degree));
//		g_Circle[i].position += m_center;
//	}
//}
////void ScaleCircle(D3DXVECTOR3 sizePresent);
//void Hook::DrawHook(LPDIRECT3DDEVICE9 device)
//{	
//	//device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, m_pointCount, m_Circle, sizeof(Vertex2d));
//	//device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, m_pointCount , m_Circle2, sizeof(Vertex2d));
//}
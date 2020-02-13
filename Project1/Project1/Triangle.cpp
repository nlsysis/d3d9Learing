#include "Triangle.h"

Triangle::Triangle()
{
}

void Triangle::InitTriangle(Vertex2d *vb)
{
	for (int i = 0;i < 3;i++)
	{
		v_Triangle[i] = vb[i];
	}
}

Triangle::~Triangle()
{
}

D3DXVECTOR4 Triangle::GetCenter()
{
	center = {0.0f, 0.0f,0.0f,0.0f};
	for (int i = 0; i < 3; i++)
	{
		center += v_Triangle[i].position;
	}
	return center/3;
}



void Triangle::DrawTriangle(LPDIRECT3DDEVICE9 device,THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount)
{
	device->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, v_Triangle, sizeof(Vertex2d));
}

void Triangle::TranslationTriangle(D3DXVECTOR3 trans)
{
	for (int i = 0; i < 3; i++)
	{
		v_Triangle[i].position.x += trans.x;
		v_Triangle[i].position.y += trans.y;
		v_Triangle[i].position.z += trans.z;
	}
}
void Triangle::RotationTriangle(float degree)
{
	D3DXVECTOR4 temp;
	D3DXVECTOR4 g_center = GetCenter();
	for (int i = 0; i < 3; i++)
	{
		temp = v_Triangle[i].position - g_center;
		v_Triangle[i].position.x = temp.x * cos(D3DXToRadian(degree))-temp.y * sin(D3DXToRadian(degree)) + g_center.x;
		v_Triangle[i].position.y = temp.x * sin(D3DXToRadian(degree))+temp.y * cos(D3DXToRadian(degree)) + g_center.y;
	}
}
void Triangle::ScaleTriangle(D3DXVECTOR3 sizePresent)
{
	D3DXVECTOR4 temp;
	D3DXVECTOR4 g_center = GetCenter();
	for (int i = 0; i < 3; i++)
	{
		temp = v_Triangle[i].position - g_center;
		v_Triangle[i].position.x = temp.x * sizePresent.x + g_center.x;
		v_Triangle[i].position.y = temp.y * sizePresent.y + g_center.y;
	}
}
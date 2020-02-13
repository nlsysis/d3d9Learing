#pragma once
#include "polygon.h"

class Circle
{
public:
	Circle();
	~Circle();
	void InitCircle(Vertex2d center, float radius, int pointCount);
	D3DXVECTOR4 GetCenter();
	void TranslationCircle(D3DXVECTOR4 trans);
	void RotationCircle(float degree);
	void ScaleCircle(D3DXVECTOR3 sizePresent);
	void DrawCircle(LPDIRECT3DDEVICE9 device);
private:
	Vertex2d *m_Circle;
	D3DXVECTOR4 m_center;
	int m_pointCount;
	int m_radius;
};

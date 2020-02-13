#pragma once
#include "polygon.h"

class Hook
{
public:
	Hook();
	~Hook();
	void InitHook(Vertex2d center, float radius, int pointCount);
	D3DXVECTOR4 GetCenter();
	void TranslationHook(D3DXVECTOR4 trans);
	void RotationHook(float degree);
	void ScaleHook(D3DXVECTOR3 sizePresent);
	void DrawHook(LPDIRECT3DDEVICE9 device);
private:
	Vertex2d *g_Circle;
	D3DXVECTOR4 m_center;
	int m_pointCount;
	int m_radius;
	//Vertex2d *m_Circle2;
};
#pragma once

#pragma once
#include "polygon.h"

class Triangle
{
public:
	Triangle();
	~Triangle();
	void InitTriangle(Vertex2d *vb);
	D3DXVECTOR4 GetCenter();
	void TranslationTriangle(D3DXVECTOR3 trans);
	void RotationTriangle(float degree);
	void ScaleTriangle(D3DXVECTOR3 sizePresent);
	void DrawTriangle(LPDIRECT3DDEVICE9 device,THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount);
private:
	Vertex2d v_Triangle[3];
	D3DXVECTOR4 center;
};


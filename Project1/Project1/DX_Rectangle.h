#pragma once
#include "polygon.h"
class DX_Rectangle
{
public:
	DX_Rectangle();
	~DX_Rectangle();
	void InitRectangle(Vertex2d rect, float height, float width);
	void InitRectangleBK(Vertex2d rect, float height, float width);
	D3DXVECTOR4 GetCenter();
	void TranslationRectangle(D3DXVECTOR3 trans);
	void ChangeRectangleColor (D3DCOLOR color);
	void RotationRectangle(float degree);
	void ScaleRectangle(D3DXVECTOR3 sizePresent);
	void DrawRectangle(LPDIRECT3DDEVICE9 device);
	void ChangeRectangleByWidth(float width);
	void ChangeRectangleByLWidth(float width);
	void ChangeRectangleByLength(float length);
	void RotationRectangleY(float degree);

private:
	Vertex2d m_Rectangle[4];
	D3DXVECTOR4 m_center;
	float m_length;
	float m_width;
};
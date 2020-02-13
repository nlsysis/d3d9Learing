#pragma once
#include "polygon.h"

class Star
{
public:
	Star();
	~Star();
	void InitStar(Vertex2d center,float br,float ir,int flag);
	void TranslationStar(D3DXVECTOR4 trans);
	void RotationStar(float degree);
	void RotationStarByPoint(Position point, float degree);
	void ScaleStar(D3DXVECTOR3 sizePresent);
	void DrawStar(LPDIRECT3DDEVICE9 device);
	void ChangeColor(D3DCOLOR color);
	Vertex2d GetStarCenter();
private:
	Vertex2d m_Star[12];
};

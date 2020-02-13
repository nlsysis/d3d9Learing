#pragma once

const int POINT_NUM = 512;
class Line
{
public:
	Line();
	~Line();
	HRESULT InitLine(D3DXVECTOR2 position, D3DCOLOR color);
	void UpdateLine();
	void DrawLine(LPDIRECT3DDEVICE9 device);
private:
	Vertex2d point[POINT_NUM];
	D3DXVECTOR4 center[POINT_NUM / 2];
};


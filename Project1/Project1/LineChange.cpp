#include "polygon.h"
#include "LineChange.h"

float dir = 1.0f;
float test = 1.0f;
Line::Line()
{
}
Line::~Line()
{
}

HRESULT Line::InitLine(D3DXVECTOR2 position, D3DCOLOR color)
{
	
	for (int i = 0,j = 0; i < POINT_NUM; i+=2,j++)
	{
		point[i] = { D3DXVECTOR4(position.x  * sin(D3DX_PI * i / 80) + i * 1.0f + position.x ,position.y + sin(D3DX_PI * i/ 128) * 100, 0.0f, 1.0f),
			D3DCOLOR_RGBA(255,255, 255,255) };
		point[i+1] = { D3DXVECTOR4((position.x + 80) * sin(D3DX_PI * (i+1)/ 80) + (i + 1) * 1.0f + position.x,(position.y + 20)+ sin(D3DX_PI * (i + 1) / 128)* 100 ,0.0f,1.0f),
			D3DCOLOR_RGBA(255, 255,255,255) };
		center[j].w = 1.0f;
		center[j].z = 0.0f;
	}
	/*point[0] = { D3DXVECTOR4(10.0f, 20.0f,0.0f,1.0f),
		D3DCOLOR_RGBA(255,255,255,255) };
	point[1] = { D3DXVECTOR4(25.0f, 30.0f,0.0f,1.0f),
		D3DCOLOR_RGBA(255,255,255,255) };*/
	return S_OK;
}

void Line::UpdateLine()
{
	
	
	
	//rotation
	for (int i = 0,j = 0; i < POINT_NUM; i++)
	{
		if (i % 2 == 0)
		{		
			center[j].x = (point[i].position.x + point[i + 1].position.x) * 0.5;
			center[j].y = (point[i].position.y + point[i + 1].position.y) * 0.5;
			j++;
		}
		D3DXVECTOR4 temp;
		temp.x = point[i].position.x - center[j-1].x;
		temp.y = point[i].position.y - center[j - 1].y;
		point[i].position.x = temp.x * cos(D3DXToRadian(5.0f)) - temp.y * sin(D3DXToRadian(5.0f)) + center[j - 1].x ;
		point[i].position.y = temp.y * cos(D3DXToRadian(5.0f)) + temp.x * sin(D3DXToRadian(5.0f)) + center[j - 1].y ;
		
	/*	D3DXVECTOR4 temp;
		temp = point[i].position;
		point[i].position.x = temp.x * cos(D3DXToRadian(5.0f)) - temp.y * sin(D3DXToRadian(5.0f));
		point[i].position.y = temp.y * cos(D3DXToRadian(5.0f)) + temp.x * sin(D3DXToRadian(5.0f));*/
	}
	////Translation
	//for (int i = 0; i < POINT_NUM; i ++)
	//{
	//	//point[i].position.x += dir * 10.0f;
	//	/*point[i].position.x += 20 * sin(D3DX_PI / 80) + 1;
	//	point[i].position.y += sin(D3DX_PI / 128) * 100 + 1;
	//	point[i + 1].position.x += 100 * sin(D3DX_PI  / 80) + 1;
	//	point[i + 1].position.y += sin(D3DX_PI / 128) * 100 + 1;*/
	//	int r = (int)(rand() % 2);
	//	int g = (int)(rand() % 2);
	//	int b = (int)(rand() % 2);
	//	point[i] = { D3DXVECTOR4(point[i].position.x * sin(D3DX_PI *(i + dir) / 80),point[i].position.y * sin(D3DX_PI * (i + dir) / 128), 0.0f, 1.0f),
	//		D3DCOLOR_RGBA(r * 255,g * 255,b * 255,255) };
	////	point[i + 1] = { D3DXVECTOR4(100 * sin(D3DX_PI * (i + 1 + dir) / 80) + (i + 1 + dir) * 1.0f + 20,320.0f + sin(D3DX_PI * (i + 1 + dir) / 128) * 100 ,0.0f,1.0f),
	//	//	D3DCOLOR_RGBA(r * 255,g * 255,b * 255,255) };
	//}
	
	if (dir <= 0 || dir>=256)
	{
		test *= -1.0f;
	}
	dir += 1.0f * test;
		

}

void Line::DrawLine(LPDIRECT3DDEVICE9 device)
{
	device->DrawPrimitiveUP(D3DPT_LINELIST, 256, point, sizeof(Vertex2d));
}
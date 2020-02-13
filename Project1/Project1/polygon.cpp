#include "polygon.h"
#include "Triangle.h"
#include "DX_Rectangle.h"
#include "Circle.h"
#include "star.h"
#include "particle.h"
#include "LineChange.h"
Triangle triangle;
DX_Rectangle rectangle;
Circle circle;
Star star1,star2;
Line line;
void InitPolygon()
{
	//Vertex2d v[]
	//{
	//	{D3DXVECTOR4(200.0f,200.0f,0.0f,1.0f),D3DCOLOR_RGBA(123,253,124,255)},
	//	{D3DXVECTOR4(300.0f,300.0f,0.0f,1.0f),D3DCOLOR_RGBA(0,0,255,255)},
	//	{D3DXVECTOR4(200.0f,350.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,0,0,255)},
	//};
	//triangle.InitTriangle(v);
	//rectangle.InitRectangle({ D3DXVECTOR4(30.0f,30.0f,0.0f,1.0f),D3DCOLOR_RGBA(0,0,255,255) }, 200.0f,300.0f);
	//circle.InitCircle({ D3DXVECTOR4(200.0f,200.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,0,255) }, 50.0f, 40);
	//star1.InitStar({ D3DXVECTOR4(200.0f,200.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,193,37,255) }, 50.0f, 25.0f,0);
	//star2.InitStar({ D3DXVECTOR4(300.0f,300.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,0,255) }, 50.0f, 25.0f,1);

	//InitParticle();
	//line.InitLine(D3DXVECTOR2(20.0f,100.0f), D3DCOLOR_RGBA(0, 255, 0, 255));
}
void UninitPolygon() 
{
	/*triangle.~Triangle();
	rectangle.~DX_Rectangle();
	circle.~Circle();*/
}
void UpdatePolygon() 
{
	//triangle.RotationTriangle(1.0f);
	//triangle.TranslationTriangle({5.0f,0.0f,0.0f});
	//triangle.ScaleTriangle({0.9f,0.9f,1.0f});

	//rectangle.RotationRectangleY(1.0f);
	//rectangle.ChangeRectangleByWidth(-10.0f);

	//circle.TranslationCircle({1.0f ,0.0f,0.0f,1.0f});
	//circle.RotationCircle(2.0f);

	//star1.RotationStar(1.0f);
	//star2.RotationStar(1.0f);

	//UpdateParticle();
	//line.UpdateLine();
}

void DrawPolygon(LPDIRECT3DDEVICE9 p_device)
{
	//triangle.DrawTriangle(p_device, D3DPT_TRIANGLELIST,1);

	//rectangle.DrawRectangle(p_device);

	//circle.DrawCircle(p_device);

	//star1.DrawStar(p_device);
	//star2.DrawStar(p_device);

	//DrawParticle(p_device);
	//line.DrawLine(p_device);
}
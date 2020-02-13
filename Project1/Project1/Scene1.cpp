#include "scene1.h"



Scene1::Scene1(float g_startTime, float g_lastTime)
	:startTime(),lastTime()
{
	startTime = g_startTime;
	lastTime = g_lastTime;
}
Scene1::~Scene1()
{
}
void Scene1::InitScene1(LPDIRECT3DDEVICE9 Device)
{
	InitParticle();
	//the font
	if (FAILED(D3DXCreateFont(Device, 60, 30, 0, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, TEXT("HGP‘n‰pŠpÎß¯Ìß‘Ì"), &g_pFont)))
		return;
	font_Rect.InitRectangle({ D3DXVECTOR4(380.0f,330.0f,0.0f,1.0f),D3DCOLOR_RGBA(0,0,0,255) }, 70.0f, 340.0f);
	win_Rect.InitRectangle({ D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f),D3DCOLOR_RGBA(0,0,0,0) }, SCREEN_HEIGHT, SCREEN_WIDTH);
	
	star.InitStar({ D3DXVECTOR4(120.0f,-44.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,193,37,255) }, 46.0f, 22.0f, 0);
	isShine = false;
	g_gravity = 1.0f;
	g_starXSpeed = 2.0f;
	g_starYSpeed = 0.0f;
	rotationCenter.x = 586.0f;
	rotationCenter.y = 450.0f;
	color_al = 0;
}
void Scene1::UpdateScene1(float currentTime)
{
	UpdateParticle();
	float lastedTime = currentTime - startTime;
	if (lastedTime < 1.2f)
	{
	}
	else if (lastedTime <5.1f)
	{
		star.RotationStar(3.0f);
		g_starYSpeed += g_gravity;
		star.TranslationStar(D3DXVECTOR4(g_starXSpeed, g_starYSpeed, 0.0f, 0.0f));
		if (star.GetStarCenter().position.y >= 380)
		{
			g_starYSpeed = -g_starYSpeed+3.0f;
		}
	}
	else if (lastedTime < 11.6f)
	{
		star.RotationStar(3.0f);
		star.TranslationStar(D3DXVECTOR4(g_starXSpeed, 0.0f, 0.0f, 0.0f));
		font_Rect.ChangeRectangleByLWidth(g_starXSpeed);
	}
	else if (lastedTime < 18.0f)
	{
		star.RotationStarByPoint(rotationCenter,3.0f);
	}
	else if (lastedTime < 20.0f)
	{
		star.RotationStarByPoint(rotationCenter, 3.0f);
		star.ScaleStar(D3DXVECTOR3(1.1f,1.1f,1.0f));
	}
	else if (lastedTime < 21.0f)
	{
		if (color_al < 255)
		{
			color_al += 15;
			win_Rect.ChangeRectangleColor(D3DCOLOR_RGBA(255, 255, 255, color_al));
		}
		
	}


	if ((int)lastedTime % 4 == 0)
	{
		isShine = true;
	}
	else
		isShine = false;
}
void Scene1::DrawScene1(LPDIRECT3DDEVICE9 Device,HWND hWnd)
{
	//‰æ–Ê‚ÌƒNƒŠƒA
	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	
	RECT formatRect;
	GetClientRect(hWnd, &formatRect);
	
	//render start
	Device->BeginScene();
	Device->SetFVF(FVF_VERTEX2D);

	//•`‚­

	//draw font
	g_pFont->DrawText(NULL, TEXT("¯™‚ð’Þ‚é"), strlen(TEXT("¯™‚ð’Þ‚é")), &formatRect, DT_SINGLELINE | DT_NOCLIP | DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(255, 39, 136));
	
	font_Rect.DrawRectangle(Device);

	DrawParticle(Device);

	star.DrawStar(Device);

	win_Rect.DrawRectangle(Device);
	


	Device->EndScene();
	Device->Present(NULL, NULL, NULL, NULL);
}

CenterMSG Scene1::GetStarMSG()
{
	CenterMSG cs;
	cs.position.x = star.GetStarCenter().position.x;
	cs.position.y = star.GetStarCenter().position.y;
	cs.isLeftDown = isShine;
	return cs;
}
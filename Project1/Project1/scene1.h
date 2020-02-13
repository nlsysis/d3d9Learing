#pragma once
#include "D3D9.h"
#include "particle.h"
#include "DX_Rectangle.h"
#include "star.h"
#include "main.h"

class Scene1
{
public:
	Scene1(float startTime, float lastTime);
	~Scene1();
	void InitScene1(LPDIRECT3DDEVICE9 Device);
	void UpdateScene1(float currentTime);
	void DrawScene1(LPDIRECT3DDEVICE9 device, HWND hWnd);
	CenterMSG GetStarMSG();
private:
	float startTime;
	float lastTime;
	ID3DXFont*	g_pFont;
	DX_Rectangle font_Rect;  // to shade the font
	Star star;
	bool isShine;
	float rectResize;
	float g_starXSpeed, g_starYSpeed, g_gravity;
	Position rotationCenter;
	DX_Rectangle win_Rect;
	int color_al;
};
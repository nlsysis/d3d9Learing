#pragma once
#include "D3D9.h"
#include "DX_Rectangle.h"
#include "star.h"
#include "Circle.h"
#include "waterWave.h"
#include "Rippling.h"
#include "waterWave2.h"
class Scene2
{
public:
	Scene2(float startTime, float lastTime);
	~Scene2();
	void InitScene2(LPDIRECT3DDEVICE9 Device);
	void UpdateScene2(float currentTime);
	void DrawScene2(LPDIRECT3DDEVICE9 device, HWND hWnd);
private:
	void waveEffect(LPDIRECT3DDEVICE9 g_pdevice);
	void waveEffect2(LPDIRECT3DDEVICE9 g_pdevice);
	float startTime;
	float lastTime;
	Star star;
	DX_Rectangle bk_rect[2];
	DX_Rectangle hook_rect[2];
	Circle hook_circle;
	float hook_speed, hook_speedUP;
	float water_force;
	float left_force;
	float right_force;
	float star_gravity;
	Rippling *m_rippling;
	
	short *waveBuffer;
	Position wavePos;
	D3DSURFACE_DESC surfaceDesc;
	IDirect3DSurface9 *surface;
	D3DLOCKED_RECT lockedRect;
	DWORD *imageData;
	DWORD *imageDataDst;
	bool isShowEffect;
	waterWave2 *ww2;
};
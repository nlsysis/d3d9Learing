#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } } 




BOOL D3D_Init(HWND);
HRESULT Objects_Init(HWND hWnd);
void UnInit();
void Update();
void Draw();

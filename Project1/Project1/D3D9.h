#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } } 

template <class T> void Release(T t)
{
	if (t)
	{
		t->Release();
		t = 0;
	}
}



BOOL D3D_Init(HWND);
HRESULT Objects_Init(HWND hWnd);
void UnInit();
void Update();
//void Draw();
LPDIRECT3DDEVICE9 GetD3DDevice();

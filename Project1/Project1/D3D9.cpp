#include "D3D9.h"
#include "main.h"
#include "polygon.h"
#include "animation.h"
/*------------------------------------------------------------
 グローバル変数を宣言
------------------------------------------------------------*/
LPDIRECT3DDEVICE9 g_pDevice = NULL;      //＊＊＊＊direct4dのデバイスを取得
D3DPRESENT_PARAMETERS d3dpp = {};

//-----------------------------------game:Init(HWND hWnd)-------------------
//	Des: Direct3Dの初期化
//--------------------------------------------------------------------------
BOOL D3D_Init(HWND hWnd)
{
	LPDIRECT3D9  g_pD3D = NULL;
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) //初期化Direct3Dインターフェース
		MessageBox(hWnd, TEXT("DirectX初期化失敗した"), TEXT("DirectX初期化"), MB_OK);

	d3dpp.BackBufferWidth = SCREEN_WIDTH;    //
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;   //バックバッファの種類
	d3dpp.BackBufferCount = 1;        //バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;  //デプスバッファ（深度情報）
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;   //デプス16ビット
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//test for water wave and it will slow the speed of calculate 
	//but it is necessary for piexl shading
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	
	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, TEXT("DirectXデバイス初期化失敗した"), TEXT("DirectX初期化"), MB_OK);
		return false;
	}

	if (!(S_OK == Objects_Init(hWnd))) return false;
	//InitPolygon();
	return true;

}
//-----------------------------------game:Objects_Init----------------------
//	Des: Direct3Dの内容を初期化
//--------------------------------------------------------------------------
HRESULT Objects_Init(HWND hWnd)
{

	return S_OK;
}
//-----------------------------------game:UnInit()-------------------
//	Des: Direct3Dの
//--------------------------------------------------------------------------
void UnInit()
{
	SAFE_RELEASE(g_pDevice);
}

//-----------------------------------game:Update()-------------------
//	Des: Direct3Dの描く内容を変更する
//--------------------------------------------------------------------------
void Update()
{
	//UpdatePolygon();
}

LPDIRECT3DDEVICE9 GetD3DDevice()
{
	return g_pDevice;
}
//-----------------------------------game:Draw()-------------------
//	Des: Direct3D内容を描く
//--------------------------------------------------------------------------

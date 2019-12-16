#include "D3D9.h"
#include "main.h"
#include "polygon.h"
#include "cube.h"
#include "grid.h"
#include "camera.h"
#include "light.h"
#include "Model.h"
#include "meshStrip.h"
#include "texture.h"
#include "particle.h"
#include "airplane.h"
#include "shadow.h"
/*------------------------------------------------------------
 グローバル変数を宣言
------------------------------------------------------------*/
LPDIRECT3DDEVICE9 g_pDevice = NULL;      //＊＊＊＊direct4dのデバイスを取得
D3DPRESENT_PARAMETERS d3dpp = {};
LPDIRECT3DTEXTURE9 treeTexture = nullptr;

float sizeX = 1.0f;
Model m_gradriel;
Model m_cart;
MeshStrip m_floor;
MeshStrip m_wall;
float gridWidth = 10.0f;
float gridHeight = 8.0f;
float wallHeight = 1.0f;

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

	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, TEXT("DirectXデバイス初期化失敗した"), TEXT("DirectX初期化"), MB_OK);
		return false;
	}

	if (!(S_OK == Objects_Init(hWnd))) return false;
	
	SetLight(g_pDevice);
	return true;

}
//-----------------------------------game:Objects_Init----------------------
//	Des: Direct3Dの内容を初期化
//--------------------------------------------------------------------------
HRESULT Objects_Init(HWND hWnd)
{
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// αブレンドを行う
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数
	
//	g_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	//InitPolygon();
	InitCube(g_pDevice);
	InitCamera(g_pDevice);
	
	
	InitGrid(sizeX, sizeX);

	LoadModel(g_pDevice, ".\\Resource\\gradriel\\gradriel.x", ".\\Resource\\gradriel\\",m_gradriel);
	LoadModel(g_pDevice, ".\\Resource\\cart\\cart.x", ".\\Resource\\cart\\",m_cart);
	
	InitGridMesh(g_pDevice, ".\\Resource\\texture\\field001.jpg",gridWidth, gridHeight,m_floor,FLOOR);
	InitGridMesh(g_pDevice, ".\\Resource\\texture\\wall003.jpg", gridWidth, wallHeight, m_wall,WALL);
	//load texture
	LoadTexture(g_pDevice, ".\\Resource\\texture\\tree001.png", treeTexture);
	
	InitParticle(g_pDevice);
	InitAirplane(g_pDevice);
//	InitShadow(g_pDevice,0.5f,0.5f);
	return S_OK;
}
//-----------------------------------game:UnInit()-------------------
//	Des: Direct3Dの
//--------------------------------------------------------------------------
void UnInit()
{
	SAFE_RELEASE(g_pDevice);
	UninitCube();
	UninitModel(m_gradriel);
	UninitModel(m_cart);
	UninitGridMesh(m_floor);
	UninitGridMesh(m_wall);
//	UninitBillboard();
	UninitTexture(treeTexture);
	UninitParticle();
	UninitAirplane();
//	UninitShadow();
}

//-----------------------------------game:Update()-------------------
//	Des: Direct3Dの描く内容を変更する
//--------------------------------------------------------------------------
void Update()
{
	//UpdatePolygon();
	//UpdateCube(g_pDevice);
	UpdateCamera(g_pDevice);
	UpdateAirplane();
	

}

//-----------------------------------game:Draw()-------------------
//	Des: Direct3D
//--------------------------------------------------------------------------
void Draw()
{
	//画面のクリア
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 80, 200, 255), 1.0f, 0);

	//render start
	g_pDevice->BeginScene();

	static float angle =0.03f;

	D3DXMATRIX matWorld,matScale,matTrans,matRoll,matTrans2;

//	D3DXMatrixTranslation(&matTrans,0.0f,1.0f,0.0f);
//	matWorld = matWorld * matTrans;
//	DrawParticle(g_pDevice, shadowTexture, matWorld);

	//mesh-floor
	D3DXMatrixIdentity(&matWorld);
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	DrawGridMesh(g_pDevice, m_floor);
	//mesh-back wall
	D3DXMatrixIdentity(&matWorld); 
	D3DXMatrixTranslation(&matTrans, 0.0f, wallHeight/2, gridHeight /2);
	matWorld = matWorld  * matTrans;
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	DrawGridMesh(g_pDevice, m_wall);

	//mesh-front wall
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matTrans, 0.0f, wallHeight / 2, -gridHeight / 2);
	D3DXMatrixRotationY(&matRoll, D3DX_PI);
	matWorld = matWorld * matRoll* matTrans;
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	DrawGridMesh(g_pDevice, m_wall);

	DrawAirplane(g_pDevice);

	//draw shadow
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matTrans, 0.0f, 1.0f, 0.0f);
	matWorld = matWorld * matTrans;
	//DrawShadow(g_pDevice, matWorld);


	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);
}
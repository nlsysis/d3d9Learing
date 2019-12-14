#include "D3D9.h"
#include "main.h"
#include "polygon.h"
#include "cube.h"
#include "grid.h"
#include "camera.h"
#include "light.h"
#include "Model.h"
#include "meshStrip.h"
#include "billboard.h"
#include "texture.h"
#include "shadow.h"
#include "particle.h"
/*------------------------------------------------------------
 グローバル変数を宣言
------------------------------------------------------------*/
LPDIRECT3DDEVICE9 g_pDevice = NULL;      //＊＊＊＊direct4dのデバイスを取得
D3DPRESENT_PARAMETERS d3dpp = {};
LPDIRECT3DTEXTURE9 treeTexture = nullptr;
LPDIRECT3DTEXTURE9 bulletTexture = nullptr;
LPDIRECT3DTEXTURE9 shadowTexture = nullptr;
float sizeX = 1.0f;

Model m_gradriel;
Model m_cart;
Model m_airplane;
MeshStrip m_floor;
MeshStrip m_wall;
float gridWidth = 10.0f;
float gridHeight = 10.0f;
float wallHeight = 5.0f;

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
	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
//	g_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	//InitPolygon();
	InitCube(g_pDevice);
	InitCamera(g_pDevice);
	
	
	InitGrid(sizeX, sizeX);

	LoadModel(g_pDevice, ".\\Resource\\gradriel\\gradriel.x", ".\\Resource\\gradriel\\",m_gradriel);
	LoadModel(g_pDevice, ".\\Resource\\cart\\cart.x", ".\\Resource\\cart\\",m_cart);
	LoadModel(g_pDevice, ".\\Resource\\airplane000.x", NULL, m_airplane);
	
	InitGridMesh(g_pDevice, ".\\Resource\\texture\\field001.jpg",gridWidth, gridHeight,m_floor);
	InitGridMesh(g_pDevice, ".\\Resource\\texture\\wall002.jpg", gridWidth, wallHeight, m_wall);
	//load texture
	LoadTexture(g_pDevice, ".\\Resource\\texture\\tree001.png", treeTexture);
	LoadTexture(g_pDevice, ".\\Resource\\texture\\bullet000.png", bulletTexture);
	LoadTexture(g_pDevice, ".\\Resource\\texture\\shadow000.jpg", shadowTexture);
	InitBillboard(g_pDevice);
	InitShadow(g_pDevice);
	InitParticle(g_pDevice);
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
	UninitModel(m_airplane);
	UninitGridMesh(m_floor);
	UninitGridMesh(m_wall);
	UninitShadow(); 
	UninitBillboard();
	UninitTexture(treeTexture);
	UninitTexture(shadowTexture);
	UninitTexture(bulletTexture);
	UninitParticle();
}

//-----------------------------------game:Update()-------------------
//	Des: Direct3Dの描く内容を変更する
//--------------------------------------------------------------------------
void Update()
{
	//UpdatePolygon();
	//UpdateCube(g_pDevice);
	UpdateCamera(g_pDevice);
	UpdateModel(m_airplane);

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

	//
	//ポリコンを描く
	//DrawPolygon(g_pDevice);
	//cube 1
	//static float size = sizeX * 0.1;
	static float size = 1.0f;
	static float angle =0.03f;
	D3DXMATRIX matWorld,matScale,matTrans,matRoll,matTrans2;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationY(&matRoll, -angle);
	//D3DXMatrixScaling(&matScale, size, size, size);
	D3DXMatrixTranslation(&matTrans,-gridWidth * 0.5 + 0.5,size * 0.5, gridHeight * 0.5 - 0.5);
	matWorld = matWorld  * matRoll* matTrans;
	angle += 0.03f;
	//DrawCube(g_pDevice, &matWorld);

	////cube 2
	//float speed = 0.05f;
	//static float vx = 0.0f, vz = 0.0f;
	//static unsigned int dir = 0;
	//switch (dir)
	//{
	//case 0: //Left
	//	vx += speed;
	//	if (vx >= gridWidth - size)
	//	{
	//		vx = gridWidth - size;
	//		dir = 1;
	//	}
	//	break;
	//case 1:  //UP
	//	vz += -speed;
	//	if (vz <= -gridHeight + size)
	//	{
	//		vz = -gridHeight + size;
	//		dir = 2;
	//	}
	//	break;
	//case 2:
	//	vx += -speed;
	//	if (vx <= 0.0f)
	//	{
	//		vx = 0.0f;
	//		dir = 3;
	//	}
	//	break;
	//case 3:
	//	vz += speed;
	//	if (vz >= 0.0f)
	//	{
	//		vz = 0.0f;
	//		dir = 0;
	//	}
	//	break;
	//}

	//D3DXMatrixIdentity(&matWorld);
	////D3DXMatrixScaling(&matScale, size, size, size);
	//D3DXMatrixTranslation(&matTrans, -gridWidth * 0.5 + size * 0.5 + vx, size * 0.5, gridHeight * 0.5 - size * 0.5 + vz);
	//matWorld = matWorld  * matTrans;
	//angle += 0.03f;
	//DrawCube(g_pDevice, &matWorld);

	////cube 3
	//static float scale = 1.0f;
	//static float theta = 0.0f;
	//static float oriScale = 0.0f;
	//scale = (sinf(theta) + 2);
	//oriScale += sinf(theta) * size;
	//D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixScaling(&matScale, size * scale, size* scale, size * scale);
	//D3DXMatrixTranslation(&matTrans, -gridWidth * 0.5 + size * 0.5, size * 0.5, -gridHeight * 0.5 + size * 0.5);
	//D3DXMatrixTranslation(&matTrans2, size * (scale - 1)  *  0.5, size * (scale - 1)  *  0.5, size * (scale - 1) * 0.5);
	//matWorld = matWorld * matScale * matTrans2 * matTrans;
	//theta += 0.03f;
	//DrawCube(g_pDevice, &matWorld);


	////cube 4
	//static float originY = 1.0f;
	//static float move = size * 5;
	//static unsigned int num = 1;
	//for (int i = 0; i < num; i++)
	//{
	//	D3DXMatrixIdentity(&matWorld);
	//	//D3DXMatrixScaling(&matScale, size, size, size);

	//	D3DXMatrixTranslation(&matTrans, gridWidth * 0.5 - size * 0.5, size * 0.5 + size * i, gridHeight * 0.5 - size * 0.5);
	//	if (i == num - 1)
	//	{
	//		D3DXMatrixTranslation(&matTrans2, 0.0f, move, 0.0f);
	//		matWorld = matWorld  * matTrans2 * matTrans;
	//	}
	//	else matWorld = matWorld * matTrans;

	//	DrawCube(g_pDevice, &matWorld);
	//}
	//move -= 0.02f;
	//if (move <= 0)
	//{
	//	move = size * 5;
	//	num++;
	//}
	//if (num > 5)
	//{
	//	move = size * 5;
	//	num = 1;
	//}


	////draw model
	//D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixTranslation(&matTrans, 1.0f, 0.0f, 0.0f);
	////D3DXMatrixScaling(&matScale, size, size, size);
	//matWorld = matWorld * matTrans;
	//g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//DrawModel(g_pDevice, m_gradriel);

	//D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixTranslation(&matTrans, -1.0f, 0.0f, 0.0f);
	////D3DXMatrixScaling(&matScale, size, size, size);
	//matWorld = matWorld *matTrans;
	//g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//DrawModel(g_pDevice, m_gradriel);

	//D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixTranslation(&matTrans, 1.0f, 0.0f, -1.0f);
	////D3DXMatrixScaling(&matScale, size, size, size);
	//matWorld = matWorld  * matTrans;
	//g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//DrawModel(g_pDevice,m_cart);

	//D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixTranslation(&matTrans, -1.0f, 0.0f, -1.0f);
	////D3DXMatrixScaling(&matScale, size, size, size);
	//matWorld = matWorld * matTrans;
	//g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//DrawModel(g_pDevice, m_cart);

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale,0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationY(&matRoll, m_airplane.rotation);
	D3DXMatrixTranslation(&matTrans, m_airplane.position.x, m_airplane.position.y, m_airplane.position.z);
	matWorld = matWorld * matRoll * matScale * matTrans;
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	DrawModel(g_pDevice,m_airplane);
	
	//grid
	//D3DXMatrixIdentity(&matWorld);
	//g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//DrawGrid(g_pDevice);

	
	//billboard
	//DrawBillboard(g_pDevice, treeTexture);
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matTrans, 0.0f, 1.0f, 0.0f);
	matWorld = matWorld * matRoll * matTrans;
	DrawParticle(g_pDevice, shadowTexture, matWorld);

	//mesh-floor
	D3DXMatrixIdentity(&matWorld);
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	DrawGridMesh(g_pDevice, m_floor);
	//mesh-wall
	//D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixTranslation(&matTrans, -1.0f, 0.0f, -1.0f);
	//D3DXMatrixRotationZ(&matRoll, -D3DX_PI / 2);
	//matWorld = matWorld * matRoll * matTrans;
	//g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//DrawGridMesh(g_pDevice, m_wall);
	
	D3DXMatrixIdentity(&matWorld);
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	DrawShadow(g_pDevice,shadowTexture,matWorld);
	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);
}
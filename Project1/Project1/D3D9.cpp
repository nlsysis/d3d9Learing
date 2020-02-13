#include "D3D9.h"
#include "main.h"
#include "polygon.h"
#include "animation.h"
/*------------------------------------------------------------
 �O���[�o���ϐ���錾
------------------------------------------------------------*/
LPDIRECT3DDEVICE9 g_pDevice = NULL;      //��������direct4d�̃f�o�C�X���擾
D3DPRESENT_PARAMETERS d3dpp = {};

//-----------------------------------game:Init(HWND hWnd)-------------------
//	Des: Direct3D�̏�����
//--------------------------------------------------------------------------
BOOL D3D_Init(HWND hWnd)
{
	LPDIRECT3D9  g_pD3D = NULL;
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) //������Direct3D�C���^�[�t�F�[�X
		MessageBox(hWnd, TEXT("DirectX���������s����"), TEXT("DirectX������"), MB_OK);

	d3dpp.BackBufferWidth = SCREEN_WIDTH;    //
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;   //�o�b�N�o�b�t�@�̎��
	d3dpp.BackBufferCount = 1;        //�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;  //�f�v�X�o�b�t�@�i�[�x���j
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;   //�f�v�X16�r�b�g
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//test for water wave and it will slow the speed of calculate 
	//but it is necessary for piexl shading
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	
	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, TEXT("DirectX�f�o�C�X���������s����"), TEXT("DirectX������"), MB_OK);
		return false;
	}

	if (!(S_OK == Objects_Init(hWnd))) return false;
	//InitPolygon();
	return true;

}
//-----------------------------------game:Objects_Init----------------------
//	Des: Direct3D�̓��e��������
//--------------------------------------------------------------------------
HRESULT Objects_Init(HWND hWnd)
{

	return S_OK;
}
//-----------------------------------game:UnInit()-------------------
//	Des: Direct3D��
//--------------------------------------------------------------------------
void UnInit()
{
	SAFE_RELEASE(g_pDevice);
}

//-----------------------------------game:Update()-------------------
//	Des: Direct3D�̕`�����e��ύX����
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
//	Des: Direct3D���e��`��
//--------------------------------------------------------------------------

#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#define CLASS_NAME "GameWindow"              //システムレジストリにアプリケーションの 名前
#define WINDOW_CAPTION "ウインドウ表示処理"    //ウィンドウタイトルバーの名前
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)
#define WINDOW_STYLEX (120)
#define WINDOW_STYLEY (20)

#define FVF_TEXTURE2D (D3DFVF_XYZ | D3DFVF_TEX1)

typedef struct TEXTURE2D_tag
{
	D3DXVECTOR3 position;      //vertex
	D3DXVECTOR2 textCoord;     //uv

	TEXTURE2D_tag(D3DXVECTOR3 in_position, D3DXVECTOR2 in_textCoord)
		:
		position(in_position),
		textCoord(in_textCoord)
	{}
}TEXTURE2D;

/*------------------------------------------------------------
  関数を宣言
------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //ウィンドウのコールバック関数
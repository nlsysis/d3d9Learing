#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#define CLASS_NAME "GameWindow"              //システムレジストリにアプリケーションの 名前
#define WINDOW_CAPTION "ウインドウ表示処理"    //ウィンドウタイトルバーの名前
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)
#define WINDOW_STYLEX (120)
#define WINDOW_STYLEY (20)

/*------------------------------------------------------------
  関数を宣言
------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //ウィンドウのコールバック関数
/*------------------------------------------------------------
DXのInit[main.cpp]

								Author：NI　JIALU
								Date：2019・05・30
------------------------------------------------------------*/

#include "main.h"
#include "D3D9.h"
#include "input.h"

#pragma comment(lib,"d3d9.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment( lib, "d3dx9.lib" )
#endif



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//警告レベル 4 (/W4)に　hPrevInstance引数が使わないと　デバッグの時　警告します
	//UNREFERENCED_PARAMETER関数を使うとこの問題を解決する
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);



	RECT window_rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	WNDCLASS wc = {};          //WNDCLASS 構造体
	wc.lpfnWndProc = WndProc;  //ウィンドウのコールバック関数ウインドウのメッセージを処理するコールバック関数へのポインタ
	wc.lpszClassName = CLASS_NAME; //ウインドウクラスにつける名前
	wc.hInstance = hInstance;   //このクラスのためのウインドウプロシージャがあるインスタンスハンドル
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);  //マウスカーソルのハンドル
	wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_BACKGROUND + 1); //ウインドウ背景色

	RegisterClass(&wc);   //システムにwcを登録する メモリを申請します

	AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX), FALSE);
	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);
	int window_x = (desktop_width - window_width) / 2;
	//int window_y = (desktop_height - window_height) / 2;
	int window_y = max((desktop_height - window_height) / 2, 0);

	//ウインドウを作る！今まで　ウインドウはまだ見えないです　メモリにある
	HWND hWnd = CreateWindow(
		CLASS_NAME,                  // RegisterClass()で登録したクラスの名前
		WINDOW_CAPTION,             // ウィンドウタイトルバーの名前
		WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX),             // ウインドウスタイル
		window_x,              // ウインドウ左上x座標
		window_y,              //ウインドウ左上y座標
		window_width,             //ウインドウ幅
		window_height,              // ウインドウ高さ
		NULL,                       // 親ウインドウのハンドル
		NULL,                       // メニューのハンドル
		hInstance,                  // 	ウインドウとかを作成するモジュールのインスタンスのハンドル
		NULL                        // WM_CREATEでLPARAMに渡したい値
	);

	ShowWindow(hWnd, nCmdShow);  //システムにWM_CREATEを送る　WndProc関数を呼び出す 実行したら　ウインドウを出る
	UpdateWindow(hWnd);   //システムにWM_PAINTを送る　WndProc関数を呼び出す

	D3D_Init(hWnd);

	Keyboard_Initialize(hInstance,hWnd);

	MSG msg = {};  //MSG構造体


	while (msg.message != WM_QUIT)   // メッセージキューと呼ばれる領域にメッセージを取得する 戻り値はBOOL型 
										   //メッセージを受け取るまで　プログラムをブロックする
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);   //キーボードのボダンのメッセージを翻訳する
			DispatchMessage(&msg);  //内部でMSG構造体のhwndメンバを用いて ウインドウプロシージャのアドレスを取得する関数を呼び出し（システムの仕事）
								   //その後、MSG構造体のメンバを引数としてウインドウプロシージャを呼び出します。
		}
		else
		{
			
			//ゲーム処理
			Update();
			Draw();
		}

	}
	UnInit();
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);  //メッセージを送る　第三、四引数のなかにメッセージの内容がある
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
		{
			DestroyWindow(hWnd);  //ウインドウを閉じる
		}
		return 0;
	case WM_DESTROY:		//アプリケーション終了
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);  //基本的な動作もサポートする
}

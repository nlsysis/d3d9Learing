/*------------------------------------------------------------
DX��Init[main.cpp]

								Author�FNI�@JIALU
								Date�F2019�E05�E30
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
	//�x�����x�� 4 (/W4)�Ɂ@hPrevInstance�������g��Ȃ��Ɓ@�f�o�b�O�̎��@�x�����܂�
	//UNREFERENCED_PARAMETER�֐����g���Ƃ��̖�����������
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);



	RECT window_rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	WNDCLASS wc = {};          //WNDCLASS �\����
	wc.lpfnWndProc = WndProc;  //�E�B���h�E�̃R�[���o�b�N�֐��E�C���h�E�̃��b�Z�[�W����������R�[���o�b�N�֐��ւ̃|�C���^
	wc.lpszClassName = CLASS_NAME; //�E�C���h�E�N���X�ɂ��閼�O
	wc.hInstance = hInstance;   //���̃N���X�̂��߂̃E�C���h�E�v���V�[�W��������C���X�^���X�n���h��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);  //�}�E�X�J�[�\���̃n���h��
	wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_BACKGROUND + 1); //�E�C���h�E�w�i�F

	RegisterClass(&wc);   //�V�X�e����wc��o�^���� ��������\�����܂�

	AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX), FALSE);
	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);
	int window_x = (desktop_width - window_width) / 2;
	//int window_y = (desktop_height - window_height) / 2;
	int window_y = max((desktop_height - window_height) / 2, 0);

	//�E�C���h�E�����I���܂Ł@�E�C���h�E�͂܂������Ȃ��ł��@�������ɂ���
	HWND hWnd = CreateWindow(
		CLASS_NAME,                  // RegisterClass()�œo�^�����N���X�̖��O
		WINDOW_CAPTION,             // �E�B���h�E�^�C�g���o�[�̖��O
		WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX),             // �E�C���h�E�X�^�C��
		window_x,              // �E�C���h�E����x���W
		window_y,              //�E�C���h�E����y���W
		window_width,             //�E�C���h�E��
		window_height,              // �E�C���h�E����
		NULL,                       // �e�E�C���h�E�̃n���h��
		NULL,                       // ���j���[�̃n���h��
		hInstance,                  // 	�E�C���h�E�Ƃ����쐬���郂�W���[���̃C���X�^���X�̃n���h��
		NULL                        // WM_CREATE��LPARAM�ɓn�������l
	);

	ShowWindow(hWnd, nCmdShow);  //�V�X�e����WM_CREATE�𑗂�@WndProc�֐����Ăяo�� ���s������@�E�C���h�E���o��
	UpdateWindow(hWnd);   //�V�X�e����WM_PAINT�𑗂�@WndProc�֐����Ăяo��

	D3D_Init(hWnd);

	Keyboard_Initialize(hInstance,hWnd);

	MSG msg = {};  //MSG�\����


	while (msg.message != WM_QUIT)   // ���b�Z�[�W�L���[�ƌĂ΂��̈�Ƀ��b�Z�[�W���擾���� �߂�l��BOOL�^ 
										   //���b�Z�[�W���󂯎��܂Ł@�v���O�������u���b�N����
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);   //�L�[�{�[�h�̃{�_���̃��b�Z�[�W��|�󂷂�
			DispatchMessage(&msg);  //������MSG�\���̂�hwnd�����o��p���� �E�C���h�E�v���V�[�W���̃A�h���X���擾����֐����Ăяo���i�V�X�e���̎d���j
								   //���̌�AMSG�\���̂̃����o�������Ƃ��ăE�C���h�E�v���V�[�W�����Ăяo���܂��B
		}
		else
		{
			
			//�Q�[������
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
			SendMessage(hWnd, WM_CLOSE, 0, 0);  //���b�Z�[�W�𑗂�@��O�A�l�����̂Ȃ��Ƀ��b�Z�[�W�̓��e������
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
		{
			DestroyWindow(hWnd);  //�E�C���h�E�����
		}
		return 0;
	case WM_DESTROY:		//�A�v���P�[�V�����I��
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);  //��{�I�ȓ�����T�|�[�g����
}

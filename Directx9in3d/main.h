#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#define CLASS_NAME "GameWindow"              //�V�X�e�����W�X�g���ɃA�v���P�[�V������ ���O
#define WINDOW_CAPTION "�E�C���h�E�\������"    //�E�B���h�E�^�C�g���o�[�̖��O
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)
#define WINDOW_STYLEX (120)
#define WINDOW_STYLEY (20)

/*------------------------------------------------------------
  �֐���錾
------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //�E�B���h�E�̃R�[���o�b�N�֐�
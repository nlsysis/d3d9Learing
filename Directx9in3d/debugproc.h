#pragma once

HRESULT InitDebugProc(LPDIRECT3DDEVICE9 pDevice);
void UninitDebugProc(void);
void UpdateDebugProc(void);
void DrawDebugProc(void);

void PrintDebugProc(const char *fmt, ...);
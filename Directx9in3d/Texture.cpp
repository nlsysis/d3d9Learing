#include "Texture.h"


int Texture_SetLoadFile(LPDIRECT3DDEVICE9 pDevice, char* fileName)
{
	LPDIRECT3DTEXTURE9 pTexture;
	HRESULT hr = D3DXCreateTextureFromFile(pDevice,fileName,&pTexture);
	if (FAILED(hr))
	{
		MessageBox(NULL, "LOAD TEXTURE Failed!!", NULL, NULL);
		return -1;
	}
	return (int)pTexture;
}

void Texture_Release(int textureId,DWORD materialCount)
{
	LPDIRECT3DTEXTURE9 pTexture = (LPDIRECT3DTEXTURE9)textureId;
	pTexture->Release();
}

LPDIRECT3DTEXTURE9 Texture_GetTexture(int textureId)
{
	return (LPDIRECT3DTEXTURE9)textureId;
}

void LoadTexture(LPDIRECT3DDEVICE9 pDevice, LPCSTR fileName, LPDIRECT3DTEXTURE9 &texture)
{
	//load texture of mesh
	if (FAILED(D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
		fileName,					// ファイルの名前
		&texture)))
	{
		MessageBox(0, "Init orient texture failed", NULL, NULL);
		return;
	}
}
void UninitTexture(LPDIRECT3DTEXTURE9 &texture)
{
	if (texture)
	{
		texture->Release();
		texture = nullptr;
	}
}
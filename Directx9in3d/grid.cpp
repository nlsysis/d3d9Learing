#include "grid.h"

const int POINTNUM = 44;
GridVertex gridVertex[POINTNUM];

void InitGrid(float sizeX,float sizeZ)
{
	float distanceX = sizeX * 0.1;
	float distanceZ = sizeZ * 0.1;
	float posX = -sizeX * 0.5;
	float posZ = -sizeZ * 0.5;
	float originX = posX;
	float originZ = posZ;
	for (int i = 0; i <= 20; i = i+2)
	{
		gridVertex[i].position = D3DXVECTOR3(posX, 0.0f, posZ);
		gridVertex[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);

		gridVertex[i + 1].position = D3DXVECTOR3(posX + sizeX, 0.0f, posZ);
		gridVertex[i + 1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		posZ += distanceZ;
	}
	posX = originX;
	posZ = originZ;
	for (int i = 22; i <= 42; i = i + 2)
	{
		gridVertex[i].position = D3DXVECTOR3(posX, 0.0f, posZ);
		gridVertex[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);

		gridVertex[i + 1].position = D3DXVECTOR3(posX, 0.0f, posZ + sizeZ);
		gridVertex[i + 1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		posX += distanceX;
	
	}
}

void DrawGrid(LPDIRECT3DDEVICE9 p_device)
{
	p_device->SetRenderState(D3DRS_LIGHTING, false); 
	p_device->SetFVF(FVF_GRID);
	p_device->SetTexture(0, nullptr);
	p_device->DrawPrimitiveUP(D3DPT_LINELIST, 22, &gridVertex, sizeof(GridVertex));
}
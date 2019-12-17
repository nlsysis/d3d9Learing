#include "billboard.h"
#include "cameraFol.h"
#include "Texture.h"

IDirect3DVertexBuffer9 *vb_billboard = nullptr;
IDirect3DIndexBuffer9 *ib_billboard = nullptr;

void InitBillboard(LPDIRECT3DDEVICE9 pDevice,float sizeX,float sizeY)
{
	Billboard_tag billboard_Vertex[] = {
		Billboard_tag(D3DXVECTOR3(-0.5f * sizeX, 0.5f * sizeY,0.0f),D3DXVECTOR2(0.0f,0.0f)),
		Billboard_tag(D3DXVECTOR3(0.5f * sizeX, 0.5f* sizeY,0.0f),D3DXVECTOR2(1.0f,0.0f)),
		Billboard_tag(D3DXVECTOR3(-0.5f * sizeX, -0.5f* sizeY,0.0f),D3DXVECTOR2(0.0f,1.0f)),
		Billboard_tag(D3DXVECTOR3(0.5f * sizeX , -0.5f* sizeY,0.0f),D3DXVECTOR2(1.0f,1.0f))
	};

	WORD billboard_indices[] = {2,0,3,1};

	pDevice->CreateVertexBuffer(4 * sizeof(Billboard_tag),
		0,
		FVF_Billboard,
		D3DPOOL_MANAGED,
		&vb_billboard,
		0);

	pDevice->CreateIndexBuffer(4 * sizeof(WORD),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&ib_billboard,
		0);

	Billboard_tag *vertices;
	vb_billboard->Lock(0, 0, (void**)&vertices, 0);
	for (int i = 0; i < 4; i++)
	{
		vertices[i] = billboard_Vertex[i];
	}
	vb_billboard->Unlock();

	WORD *indices;
	ib_billboard->Lock(0, 0, (void**)&indices, 0);
	for (int i = 0; i < 4; i++)
	{
		indices[i] = billboard_indices[i];
	}
	ib_billboard->Unlock();
}
void UpdateBillboard()
{

}
void DrawBillboard(LPDIRECT3DDEVICE9 pDevice,LPDIRECT3DTEXTURE9 textureBillboard, D3DXMATRIX matWorld)
{
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//another way using transpose matrix
	D3DXMATRIX matView = GetFolViewMatrix();
	D3DXMatrixTranspose(&matView,&matView);
	matView._14 = 0.0f;
	matView._24 = 0.0f;
	matView._34 = 0.0f;
	matWorld = matView * matWorld;
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);
//	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//alpha blending 
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000081);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	
	pDevice->SetFVF(FVF_Billboard);
	pDevice->SetStreamSource(0,vb_billboard,0,sizeof(Billboard_tag));
	pDevice->SetIndices(ib_billboard);
	pDevice->SetTexture(0, textureBillboard);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,4,0,2);
	pDevice->SetTexture(0, nullptr);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
//	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


}

void UninitBillboard()
{
	if (vb_billboard)
	{
		vb_billboard->Release();
		vb_billboard = 0;
	}
	if (ib_billboard)
	{
		ib_billboard->Release();
		ib_billboard = 0;
	}
}
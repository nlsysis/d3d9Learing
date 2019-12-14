#include "billboard.h"
#include "camera.h"
#include "Texture.h"

IDirect3DVertexBuffer9 *vb_billboard = nullptr;
IDirect3DIndexBuffer9 *ib_billboard = nullptr;

void InitBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	Billboard_tag billboard_Vertex[] = {
		Billboard_tag(D3DXVECTOR3(-0.5f,0.5f,0.0f),D3DXVECTOR2(0.0f,0.0f)),
		Billboard_tag(D3DXVECTOR3(0.5f,0.5f,0.0f),D3DXVECTOR2(1.0f,0.0f)),
		Billboard_tag(D3DXVECTOR3(-0.5f,-0.5f,0.0f),D3DXVECTOR2(0.0f,1.0f)),
		Billboard_tag(D3DXVECTOR3(0.5f,-0.5f,0.0f),D3DXVECTOR2(1.0f,1.0f))
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
	//calculate the billboard position
	//D3DXVECTOR3 camPos = GetCameraPosition();
	//float angle = atan2(billboardPos.x - camPos.x , billboardPos.z - camPos.z);
	//D3DXMATRIX matWorld, matRoll, matTrans;
	//D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixRotationY(&matRoll,angle);
	//D3DXMatrixTranslation(&matTrans, billboardPos.x, billboardPos.y, billboardPos.z);
	//matWorld = matWorld * matRoll * matTrans;

	//another way using transpose matrix
	D3DXMATRIX matView = GetViewMatrix();
	D3DXMatrixTranspose(&matView,&matView);
	matView._14 = 0.0f;
	matView._24 = 0.0f;
	matView._34 = 0.0f;
	matWorld = matView * matWorld;
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	/*the center will be white*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);   //for effect
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//alpha blending 
	//pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000081);
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,true);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	
	pDevice->SetFVF(FVF_Billboard);
	pDevice->SetStreamSource(0,vb_billboard,0,sizeof(Billboard_tag));
	pDevice->SetIndices(ib_billboard);
	pDevice->SetTexture(0, textureBillboard);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,4,0,2);
	pDevice->SetTexture(0, nullptr);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
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
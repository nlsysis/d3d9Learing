#include "shadow.h"
#include "texture.h"

LPDIRECT3DTEXTURE9 textureShadow = nullptr;
IDirect3DVertexBuffer9 *vb_shadow = nullptr;
IDirect3DIndexBuffer9 *ib_shadow = nullptr;

void InitShadow(LPDIRECT3DDEVICE9 pDevice,float sizeX,float sizeZ)
{
	pDevice->CreateVertexBuffer(4 * sizeof(Shadow_tag),
		0,
		FVF_Shadow,
		D3DPOOL_MANAGED,
		&vb_shadow,
		0);

	pDevice->CreateIndexBuffer(4 * sizeof(WORD),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&ib_shadow,
		0);

	Shadow_tag *vertices;
	vb_shadow->Lock(0, 0, (void**)&vertices, 0);
	vertices[0] = Shadow_tag(D3DXVECTOR3(-0.5f * sizeX, 0.0f, 0.5f * sizeZ), D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255,255,255,100),D3DXVECTOR2(0.0f, 0.0f));
	vertices[1] = Shadow_tag(D3DXVECTOR3(0.5f * sizeX, 0.0f, 0.5f* sizeZ), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 100), D3DXVECTOR2(1.0f, 0.0f));
	vertices[2] = Shadow_tag(D3DXVECTOR3(-0.5f * sizeX, 0.0f, -0.5f* sizeZ), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 100), D3DXVECTOR2(0.0f, 1.0f));
	vertices[3] = Shadow_tag(D3DXVECTOR3(0.5f * sizeX, 0.0f, -0.5f* sizeZ), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,100),D3DXVECTOR2(1.0f, 1.0f));
	vb_shadow->Unlock();

	WORD *indices;
	ib_shadow->Lock(0, 0, (void**)&indices, 0);
	indices[0] = 2;
	indices[1] = 0;
	indices[2] = 3;
	indices[3] = 1;
	ib_shadow->Unlock();

	LoadTexture(pDevice, ".\\Resource\\texture\\shadow000.jpg", textureShadow);
}
void UpdateShadow()
{

}
void DrawShadow(LPDIRECT3DDEVICE9 pDevice, D3DXMATRIX matWorld)
{
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	/*the center will be black*/
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);

	//pDevice->SetTextureStageState(0,D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_COUNT2 | D3DTTFF_DISABLE);
	pDevice->SetFVF(FVF_Shadow);
	pDevice->SetStreamSource(0, vb_shadow, 0, sizeof(Shadow_tag));
	pDevice->SetIndices(ib_shadow);
	pDevice->SetTexture(0, textureShadow);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
	pDevice->SetTexture(0, nullptr);
	// 通常ブレンドに戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// 結果 = 転送元(SRC) + 転送先(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	
}

void UninitShadow()
{
	if (vb_shadow)
	{
		vb_shadow->Release();
		vb_shadow = nullptr;
	}
	if (ib_shadow)
	{
		ib_shadow->Release();
		ib_shadow = nullptr;
	}
}
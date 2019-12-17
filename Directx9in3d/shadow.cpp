#include "shadow.h"
#include "texture.h"


void InitShadow(LPDIRECT3DDEVICE9 pDevice,float sizeX,float sizeZ,ShadowType &in_shadow)
{
	pDevice->CreateVertexBuffer(4 * sizeof(Shadow_tag),
		0,
		FVF_Shadow,
		D3DPOOL_MANAGED,
		&in_shadow.vb_shadow,
		0);

	pDevice->CreateIndexBuffer(4 * sizeof(WORD),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&in_shadow.ib_shadow,
		0);

	Shadow_tag *vertices;
	in_shadow.vb_shadow->Lock(0, 0, (void**)&vertices, 0);
	vertices[0] = Shadow_tag(D3DXVECTOR3(-0.5f * sizeX, 0.0f, 0.5f * sizeZ), D3DXVECTOR3(0.0f,1.0f,0.0f), D3DCOLOR_RGBA(255,255,255,100),D3DXVECTOR2(0.0f, 0.0f));
	vertices[1] = Shadow_tag(D3DXVECTOR3(0.5f * sizeX, 0.0f, 0.5f* sizeZ), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 100), D3DXVECTOR2(1.0f, 0.0f));
	vertices[2] = Shadow_tag(D3DXVECTOR3(-0.5f * sizeX, 0.0f, -0.5f* sizeZ), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 100), D3DXVECTOR2(0.0f, 1.0f));
	vertices[3] = Shadow_tag(D3DXVECTOR3(0.5f * sizeX, 0.0f, -0.5f* sizeZ), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,100),D3DXVECTOR2(1.0f, 1.0f));
	in_shadow.vb_shadow->Unlock();

	WORD *indices;
	in_shadow.ib_shadow->Lock(0, 0, (void**)&indices, 0);
	indices[0] = 2;
	indices[1] = 0;
	indices[2] = 3;
	indices[3] = 1;
	in_shadow.ib_shadow->Unlock();

	LoadTexture(pDevice, ".\\Resource\\texture\\shadow000.jpg", in_shadow.textureShadow);
}
void UpdateShadow()
{

}
void DrawShadow(LPDIRECT3DDEVICE9 pDevice, D3DXMATRIX matWorld, ShadowType &in_shadow)
{
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	/*the center will be black*/
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// Z比較なし
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);

	//pDevice->SetTextureStageState(0,D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_COUNT2 | D3DTTFF_DISABLE);
	pDevice->SetFVF(FVF_Shadow);
	pDevice->SetStreamSource(0, in_shadow.vb_shadow, 0, sizeof(Shadow_tag));
	pDevice->SetIndices(in_shadow.ib_shadow);
	pDevice->SetTexture(0, in_shadow.textureShadow);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
	pDevice->SetTexture(0, nullptr);
	// 通常ブレンドに戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// 結果 = 転送元(SRC) + 転送先(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
		// Z比較あり
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

}

void UninitShadow(ShadowType &in_shadow)
{
	if (in_shadow.vb_shadow)
	{
		in_shadow.vb_shadow->Release();
		in_shadow.vb_shadow = nullptr;
	}
	if (in_shadow.ib_shadow)
	{
		in_shadow.ib_shadow->Release();
		in_shadow.ib_shadow = nullptr;
	}
}
#include "particle.h"
#include "camera.h"
#include "Texture.h"

IDirect3DVertexBuffer9 *vb_particle = nullptr;
IDirect3DIndexBuffer9 *ib_particle = nullptr;

void InitParticle(LPDIRECT3DDEVICE9 pDevice)
{
	WORD particle_indices[] = { 2,0,3,1 };

	pDevice->CreateVertexBuffer(4 * sizeof(Particle_tag),
		0,
		FVF_Particle,
		D3DPOOL_MANAGED,
		&vb_particle,
		0);

	pDevice->CreateIndexBuffer(4 * sizeof(WORD),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&ib_particle,
		0);

	Particle_tag *vertices;
	vb_particle->Lock(0, 0, (void**)&vertices, 0);
	vertices[0] = Particle_tag(D3DXVECTOR3(-0.5f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 100), D3DXVECTOR2(0.0f, 0.0f));
	vertices[1] = Particle_tag(D3DXVECTOR3(0.5f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 100), D3DXVECTOR2(1.0f, 0.0f));
	vertices[2] = Particle_tag(D3DXVECTOR3(-0.5f, -0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 100), D3DXVECTOR2(0.0f, 1.0f));
	vertices[3] = Particle_tag(D3DXVECTOR3(0.5f, -0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 100), D3DXVECTOR2(1.0f, 1.0f));

	vb_particle->Unlock();

	WORD *indices;
	ib_particle->Lock(0, 0, (void**)&indices, 0);
	for (int i = 0; i < 4; i++)
	{
		indices[i] = particle_indices[i];
	}
	ib_particle->Unlock();
}
void UpdateParticle()
{

}
void DrawParticle(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DTEXTURE9 textureParticle, D3DXMATRIX matWorld)
{
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);


	/*the center will be white*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);   //for effect
	////alpha blending 
	//pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000081);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//transpose view matrix
	D3DXMATRIX matView = GetViewMatrix();
	D3DXMatrixTranspose(&matView, &matView);
	matView._14 = 0.0f;
	matView._24 = 0.0f;
	matView._34 = 0.0f;
	matWorld = matView * matWorld;
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	pDevice->SetFVF(FVF_Particle);
	pDevice->SetStreamSource(0, vb_particle, 0, sizeof(Particle_tag));
	pDevice->SetIndices(ib_particle);
	pDevice->SetTexture(0, textureParticle);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
	//pDevice->SetTexture(0, nullptr);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// 結果 = 転送元(SRC) + 転送先(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void UninitParticle()
{
	if (vb_particle)
	{
		vb_particle->Release();
		vb_particle = 0;
	}
	if (ib_particle)
	{
		ib_particle->Release();
		ib_particle = 0;
	}
}
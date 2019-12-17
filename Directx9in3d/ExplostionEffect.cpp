#include "ExplostionEffect.h"
#include "cameraFol.h"
#include "texture.h"

EXPLOSSION m_explossion[EXPLOSSION_MAX];
IDirect3DVertexBuffer9 *vb_explossion = nullptr;
IDirect3DIndexBuffer9 *ib_explossion = nullptr;
LPDIRECT3DTEXTURE9 explossionTexture = nullptr;

void InitExplossion(LPDIRECT3DDEVICE9 pDevice, float sizeX, float sizeY)
{
	TEXTURE2D_tag billboard_Vertex[] = {
		TEXTURE2D_tag(D3DXVECTOR3(-0.5f * sizeX, 0.5f * sizeY,0.0f),D3DXVECTOR2(0.0f,0.0f)),
		TEXTURE2D_tag(D3DXVECTOR3(0.5f * sizeX, 0.5f* sizeY,0.0f),D3DXVECTOR2(0.125,0.0f)),
		TEXTURE2D_tag(D3DXVECTOR3(-0.5f * sizeX, -0.5f* sizeY,0.0f),D3DXVECTOR2(0.0f,1.0f)),
		TEXTURE2D_tag(D3DXVECTOR3(0.5f * sizeX , -0.5f* sizeY,0.0f),D3DXVECTOR2(0.125,1.0f))
	};

	WORD billboard_indices[] = { 2,0,3,1 };

	pDevice->CreateVertexBuffer(4 * sizeof(TEXTURE2D_tag),
		0,
		FVF_TEXTURE2D,
		D3DPOOL_MANAGED,
		&vb_explossion,
		0);

	pDevice->CreateIndexBuffer(4 * sizeof(WORD),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&ib_explossion,
		0);

	TEXTURE2D_tag *vertices;
	vb_explossion->Lock(0, 0, (void**)&vertices, 0);
	for (int i = 0; i < 4; i++)
	{
		vertices[i] = billboard_Vertex[i];
	}
	vb_explossion->Unlock();

	WORD *indices;
	ib_explossion->Lock(0, 0, (void**)&indices, 0);
	for (int i = 0; i < 4; i++)
	{
		indices[i] = billboard_indices[i];
	}
	ib_explossion->Unlock();

	for (int i = 0; i < EXPLOSSION_MAX; i++)
	{
		m_explossion[i].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_explossion[i].nFrame = 0;
		m_explossion[i].totalFrame = 8;
		m_explossion[i].isUsed = false;
		m_explossion[i].age = 0;
	}

	LoadTexture(pDevice,".\\Resource\\explosion000.png", explossionTexture);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}

void SetExplossion(D3DXVECTOR3 in_pos)
{
	for (int i = 0; i < EXPLOSSION_MAX; i++)
	{
		if (m_explossion[i].isUsed) continue;
		m_explossion[i].position = in_pos;
		m_explossion[i].nFrame = 1;
		m_explossion[i].isUsed = true;
		m_explossion[i].age = 0;
		break;
	}
}
void DrawExplossion(LPDIRECT3DDEVICE9 pDevice)
{
	for (int i = 0; i < EXPLOSSION_MAX; i++)
	{
		if (m_explossion[i].isUsed)
		{
			
			//draw explossion
			pDevice->SetRenderState(D3DRS_LIGHTING, false);
			//another way using transpose matrix
			D3DXMATRIX matView = GetFolViewMatrix();
			D3DXMATRIX matWorld,matTrans,matScale, matTrans2;
			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixTranspose(&matView, &matView);
			matView._14 = 0.0f;
			matView._24 = 0.0f;
			matView._34 = 0.0f;
			D3DXMatrixTranslation(&matTrans, m_explossion[i].position.x, m_explossion[i].position.y, m_explossion[i].position.z -1.0f);

			matWorld = matView * matWorld * matTrans;
			pDevice->SetTransform(D3DTS_WORLD, &matWorld);
			//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				//alpha blending 
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
			pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000010);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			m_explossion[i].nFrame = m_explossion[i].age / 8;
			pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
			D3DXMatrixIdentity(&matWorld);
			matWorld._31 += 0.125 * m_explossion[i].nFrame;
			matWorld._44 = 0.0f;
			pDevice->SetTransform(D3DTS_TEXTURE0, &matWorld);
			

			pDevice->SetFVF(FVF_TEXTURE2D);
			pDevice->SetStreamSource(0, vb_explossion, 0, sizeof(TEXTURE2D_tag));
			pDevice->SetIndices(ib_explossion);
			pDevice->SetTexture(0, explossionTexture);
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
			pDevice->SetTexture(0, nullptr);
			pDevice->SetRenderState(D3DRS_LIGHTING, true);
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
			pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
		//	m_explossion[i].nFrame++;
			if (m_explossion[i].nFrame > m_explossion[i].totalFrame)
			{
				m_explossion[i].isUsed = false;
			}
			//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			m_explossion[i].age++;
		}
	}
	
}

void UninitExplossion()
{
	if (vb_explossion)
	{
		vb_explossion->Release();
		vb_explossion = 0;
	}
	if (ib_explossion)
	{
		ib_explossion->Release();
		ib_explossion = 0;
	}
}
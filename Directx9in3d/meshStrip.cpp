#include "meshStrip.h"
#include <vector>
#include "Texture.h"

//const float  centH = 20.0f;
//const float  centW = 20.0f;
int vertexTotal = 0;
int indiceNum = 0;


void InitGridMesh(LPDIRECT3DDEVICE9 pDevice, LPCSTR textureFileName ,int widthNum, int heightNum, 
	float centW,float centH,MeshStrip &in_mesh, MESHTYPE type)
{
	LoadTexture(pDevice, textureFileName, in_mesh.textureMesh);

	int centH_Num = heightNum;
	int centW_Num = widthNum;

	int vertexW = centW_Num + 1;
	int vertexH = centH_Num + 1;

	//init vertex buffer
	vertexTotal = vertexH * vertexW;
	D3DXVECTOR3 meshNormal(0.0f, 1.0f, 0.0f);
	pDevice->CreateVertexBuffer(vertexTotal * sizeof(MeshGridVertex_tag),
		0,
		FVF_MESH,
		D3DPOOL_MANAGED,
		&in_mesh.vb_meshBuffer,
		0);
	if (type == FLOOR)
	{
		MeshGridVertex_tag *pVertices;
		in_mesh.vb_meshBuffer->Lock(0, 0, (void**)&pVertices, 0);
		for (int i = 0; i < vertexH; i++)
		{
			for (int j = 0; j < vertexW; j++)
			{
				pVertices[i * vertexW + j].position = D3DXVECTOR3((-centW_Num * 0.5 + j)* centW, 0.0f, (centH_Num * 0.5 - i)* centH);
				pVertices[i * vertexW + j].normal = meshNormal;
				pVertices[i * vertexW + j].textCoord = D3DXVECTOR2(j, i);
				pVertices[i * vertexW + j].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
		}
		in_mesh.vb_meshBuffer->Unlock();

	}
	if (type == WALL)
	{
		MeshGridVertex_tag *pVertices;
		in_mesh.vb_meshBuffer->Lock(0, 0, (void**)&pVertices, 0);
		for (int i = 0; i < vertexH; i++)
		{
			for (int j = 0; j < vertexW; j++)
			{
				pVertices[i * vertexW + j].position = D3DXVECTOR3((-centW_Num * 0.5 + j)* centW, (centH_Num * 0.5 - i)* centH,0.0f);
				pVertices[i * vertexW + j].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);;
				pVertices[i * vertexW + j].textCoord = D3DXVECTOR2(j, i);
				pVertices[i * vertexW + j].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
		}
		in_mesh.vb_meshBuffer->Unlock();

	}
	//init index buffer
	indiceNum = 2 * vertexW * (vertexH - 1) + 2 * (vertexH);
	pDevice->CreateIndexBuffer((indiceNum - 2) * sizeof(WORD),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&in_mesh.ib_meshBuffer,
		0);

	WORD *indices;
	in_mesh.ib_meshBuffer->Lock(0,0,(void**)&indices,0);
	int countIndex = 0;
	for (int i = 0; i < vertexH - 1; i++)
	{
		for (int j = 0; j < vertexW; j++)
		{
			indices[countIndex++] = ((i + 1) * vertexW + j);
			indices[countIndex++] = (i * vertexW + j);
		}
		if (countIndex >= indiceNum - 2) continue;
		//degenerate triangle
		indices[countIndex++] = (i * vertexW + vertexW - 1);
		indices[countIndex++] = ((i + 2) * vertexW);
	}
	in_mesh.ib_meshBuffer->Unlock();

	in_mesh.primCount = (centH_Num * centW_Num ) * 2 + (centH_Num - 1) * 4;
}

void UninitGridMesh(MeshStrip &in_mesh)
{
	if(in_mesh.vb_meshBuffer != nullptr)
		in_mesh.vb_meshBuffer->Release();
	if (in_mesh.vb_meshBuffer != nullptr)
		in_mesh.ib_meshBuffer->Release();
}
void DrawGridMesh(LPDIRECT3DDEVICE9 pDevice,MeshStrip &in_mesh)
{
	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	pDevice->SetStreamSource(0, in_mesh.vb_meshBuffer, 0, sizeof(MeshGridVertex_tag));
	pDevice->SetIndices(in_mesh.ib_meshBuffer);
	pDevice->SetFVF(FVF_MESH);
	pDevice->SetTexture(0, in_mesh.textureMesh);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0,vertexTotal,0, in_mesh.primCount);
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
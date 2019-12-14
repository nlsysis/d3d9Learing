#include "cube.h"

LPDIRECT3DTEXTURE9 textureCube;
const LPCSTR textFile = { ".\\Resource\\spice_and_wolf.png" };
IDirect3DVertexBuffer9* vb_cube;
IDirect3DIndexBuffer9 *ib_cube;

void InitCube(LPDIRECT3DDEVICE9 p_device)
{
	if (FAILED(D3DXCreateTextureFromFile(p_device,	// デバイスのポインタ
		textFile,					// ファイルの名前
		&textureCube)))
	{
		MessageBox(0, "Init orient texture failed", NULL, NULL);
		return;
	}
	p_device->CreateVertexBuffer(24 * sizeof(CubeVertex_tag),
		0,
		FVF_CUBE,
		D3DPOOL_MANAGED,
		&vb_cube,
		0);
	p_device->CreateIndexBuffer(36 * sizeof(UINT),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED, 
		&ib_cube,
		0);

	CubeVertex Vertex[8]
	{
		{D3DXVECTOR3(-0.5f,0.5f,-0.5f)},  //0
		{D3DXVECTOR3(0.5f,0.5f,-0.5f)},  //1
		{D3DXVECTOR3(-0.5f,-0.5f,-0.5f)},  //2
		{D3DXVECTOR3(0.5f,-0.5f,-0.5f)},  //3

		{D3DXVECTOR3(0.5f,0.5f,0.5f)},  //4
		{D3DXVECTOR3(-0.5f,0.5f,0.5f)},  //5
		{D3DXVECTOR3(0.5f,-0.5f,0.5f)}, //6
		{D3DXVECTOR3(-0.5f,-0.5f,0.5f)},  //7
	};

	D3DCOLOR color_white = D3DCOLOR_RGBA(255, 255, 255, 255);

	CubeVertex g_cube_vertex[] = {
		//front
		{Vertex[0].position,D3DXVECTOR3(0.0f,0.0f,-1.0f),color_white,D3DXVECTOR2(0.0f,0.0f)},
		{Vertex[1].position,D3DXVECTOR3(0.0f,0.0f,-1.0f),color_white,D3DXVECTOR2(0.25f,0.0f)},
		{Vertex[2].position,D3DXVECTOR3(0.0f,0.0f,-1.0f),color_white,D3DXVECTOR2(0.0f,0.25f)},

		//{Vertex[2].position,D3DXVECTOR3(0.0f,0.0f,-1.0f),color_white,D3DXVECTOR2(0.0f,1.0f)},
		//{Vertex[1].position,D3DXVECTOR3(0.0f,0.0f,-1.0f),color_white,D3DXVECTOR2(1.0f,0.0f)},
		{Vertex[3].position,D3DXVECTOR3(0.0f,0.0f,-1.0f),color_white,D3DXVECTOR2(0.25f,0.25f)},
		//back
		{Vertex[4].position,D3DXVECTOR3(0.0f,0.0f,1.0f),color_white,D3DXVECTOR2(0.25f,0.0f)},
		{Vertex[5].position,D3DXVECTOR3(0.0f,0.0f,1.0f),color_white,D3DXVECTOR2(0.5f,0.0f)},
		{Vertex[6].position,D3DXVECTOR3(0.0f,0.0f,1.0f),color_white,D3DXVECTOR2(0.25f,0.25f)},

		//{Vertex[6].position,D3DXVECTOR3(0.0f,0.0f,1.0f),color_white,D3DXVECTOR2(0.0f,1.0f)},
		//{Vertex[5].position,D3DXVECTOR3(0.0f,0.0f,1.0f),color_white,D3DXVECTOR2(1.0f,0.0f)},
		{Vertex[7].position,D3DXVECTOR3(0.0f,0.0f,1.0f),color_white,D3DXVECTOR2(0.5f,0.25f)},
		//left
		{Vertex[5].position,D3DXVECTOR3(-1.0f,0.0f,0.0f),color_white,D3DXVECTOR2(0.5f,0.0f)},
		{Vertex[0].position,D3DXVECTOR3(-1.0f,0.0f,0.0f),color_white,D3DXVECTOR2(0.75f,0.0f)},
		{Vertex[7].position,D3DXVECTOR3(-1.0f,0.0f,0.0f),color_white,D3DXVECTOR2(0.5f,0.25f)},

		//{Vertex[7].position,D3DXVECTOR3(-1.0f,0.0f,0.0f),color_white,D3DXVECTOR2(0.0f,1.0f)},
		//{Vertex[0].position,D3DXVECTOR3(-1.0f,0.0f,0.0f),color_white,D3DXVECTOR2(1.0f,0.0f)},
		{Vertex[2].position,D3DXVECTOR3(-1.0f,0.0f,0.0f),color_white,D3DXVECTOR2(0.75f,0.25f)},

		//right
		{Vertex[1].position,D3DXVECTOR3(1.0f,0.0f,0.0f),color_white,D3DXVECTOR2(0.75f,0.0f)},
		{Vertex[4].position,D3DXVECTOR3(1.0f,0.0f,0.0f),color_white,D3DXVECTOR2(1.0f,0.0f)},
		{Vertex[3].position,D3DXVECTOR3(1.0f,0.0f,0.0f),color_white,D3DXVECTOR2(0.75f,0.25f)},

		//{Vertex[3].position,D3DXVECTOR3(1.0f,0.0f,0.0f),color_white,D3DXVECTOR2(0.0f,1.0f)},
		//{Vertex[4].position,D3DXVECTOR3(1.0f,0.0f,0.0f),color_white,D3DXVECTOR2(1.0f,0.0f)},
		{Vertex[6].position,D3DXVECTOR3(1.0f,0.0f,0.0f),color_white,D3DXVECTOR2(1.0f,0.25f)},
		//up
		{Vertex[5].position,D3DXVECTOR3(0.0f,1.0f,0.0f),color_white,D3DXVECTOR2(0.0f,0.25f)},
		{Vertex[4].position,D3DXVECTOR3(0.0f,1.0f,0.0f),color_white,D3DXVECTOR2(0.25f,0.25f)},
		{Vertex[0].position,D3DXVECTOR3(0.0f,1.0f,0.0f),color_white,D3DXVECTOR2(0.0f,0.5f)},

		//{Vertex[0].position,D3DXVECTOR3(0.0f,1.0f,0.0f),color_white,D3DXVECTOR2(0.0f,1.0f)},
		//{Vertex[4].position,D3DXVECTOR3(0.0f,1.0f,0.0f),color_white,D3DXVECTOR2(1.0f,0.0f)},
		{Vertex[1].position,D3DXVECTOR3(0.0f,1.0f,0.0f),color_white,D3DXVECTOR2(0.25f,0.5f)},
		////down
		{Vertex[6].position,D3DXVECTOR3(0.0f,-1.0f,0.0f),color_white,D3DXVECTOR2(0.25f,0.25f)},
		{Vertex[7].position,D3DXVECTOR3(0.0f,-1.0f,0.0f),color_white,D3DXVECTOR2(0.5f,0.25f)},
		{Vertex[3].position,D3DXVECTOR3(0.0f,-1.0f,0.0f),color_white,D3DXVECTOR2(0.25f,0.5f)},

		//{Vertex[3].position,D3DXVECTOR3(0.0f,-1.0f,0.0f),color_white,D3DXVECTOR2(0.0f,1.0f)},
		//{Vertex[7].position,D3DXVECTOR3(0.0f,-1.0f,0.0f),color_white,D3DXVECTOR2(1.0f,0.0f)},
		{Vertex[2].position,D3DXVECTOR3(0.0f,-1.0f,0.0f),color_white,D3DXVECTOR2(0.5f,0.5f)},

	};
	WORD g_cube_indices[] =
	{
		0,1,2,        2,1,3,
		4,5,6,        6,5,7,
		8,9,10,       10,9,11,
		12,13,14,     14,13,15,
		16,17,18,     18,17,19,
		20,21,22,     22,21,23,
	};


	CubeVertex_tag *vertices;
	vb_cube->Lock(0, 0, (void**)&vertices,0);
	for (int i = 0; i < 24; i++)
	{
		vertices[i] = g_cube_vertex[i];
	}
	vb_cube->Unlock();

	WORD *indices;
	ib_cube->Lock(0, 0, (void**)&indices, 0);
	for (int i = 0; i < 36; i++)
	{
		indices[i] = g_cube_indices[i];
	}
	ib_cube->Unlock();
	//p_device->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
}
void UpdateCube(LPDIRECT3DDEVICE9 p_device)
{
	
}
void UninitCube()
{
	vb_cube->Release();
	ib_cube->Release();
}
void DrawCube(LPDIRECT3DDEVICE9 p_device,const D3DXMATRIX* mat)
{
	p_device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	p_device->SetStreamSource(0,vb_cube,0,sizeof(CubeVertex_tag));
	p_device->SetIndices(ib_cube);
	p_device->SetFVF(FVF_CUBE);
	p_device->SetTexture(0, textureCube);

	p_device->SetTransform(D3DTS_WORLD, mat);
	
	p_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,24,0,12);
	p_device->SetTexture(0, nullptr);
	//p_device->DrawPrimitiveUP(D3DPT_TRIANGLELIST,12, &g_cube_vertex,sizeof(CubeVertex_tag));

	/*D3DXMATRIX matWorld, matTranslation;
	D3DXMatrixTranslation(&matTranslation, 3.0f, 0.0f, 0.0f);
	matWorld = matTranslation;
	p_device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &g_cube_vertex, sizeof(CubeVertex_tag));*/
}
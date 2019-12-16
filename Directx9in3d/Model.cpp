#include "Model.h"
#include "Texture.h"

#define TEXTURE_FILEPATH ".\\Resource\\gradriel\\"

/**
 load model
**/
bool LoadModel(LPDIRECT3DDEVICE9 pDevice,LPCTSTR modelFile,LPCSTR texturePath,Model &in_model)
{
	LPD3DXBUFFER pMaterialBuffer;
	HRESULT hr = D3DXLoadMeshFromX(
	//".\\Resource\\gradriel\\gradriel.x",
	modelFile,
	D3DXMESH_MANAGED | D3DXMESH_32BIT,
		pDevice,
		NULL,
		&pMaterialBuffer,
		NULL,
		&in_model.g_MaterialCount,
		&in_model.g_pMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL,"LOAD Model Failed!!",NULL,NULL);
		return false;
	}

	//マテリアルの取得
	D3DXMATERIAL *pMaterial = (D3DXMATERIAL*)pMaterialBuffer->GetBufferPointer();
	in_model.g_pTextureIds = new int[in_model.g_MaterialCount];
	in_model.g_pMaterial = new D3DMATERIAL9[in_model.g_MaterialCount];

	for (int i = 0; i < in_model.g_MaterialCount; i++)
	{
		if (pMaterial[i].pTextureFilename == NULL)
		{
			//マテリアルカラー
			ZeroMemory(&in_model.g_pMaterial[i], sizeof(D3DMATERIAL9));
			in_model.g_pMaterial[i] = pMaterial[i].MatD3D;  //ディフェーズ　diffuse　アンビエント　ambient　エミッシブ　Emissive
			in_model.g_pMaterial[i].Ambient = in_model.g_pMaterial[i].Diffuse;
		}
 		else
		{
			in_model.g_pTextureIds[i] = -1;
			//red
			in_model.g_pMaterial[i].Diffuse.r = in_model.g_pMaterial[i].Ambient.r = 1.0f;
			in_model.g_pMaterial[i].Diffuse.g = in_model.g_pMaterial[i].Ambient.g = 1.0f;
			in_model.g_pMaterial[i].Diffuse.b = in_model.g_pMaterial[i].Ambient.b = 1.0f;
			in_model.g_pMaterial[i].Diffuse.a = in_model.g_pMaterial[i].Ambient.a = 1.0f;
			//エミッシブは0.0fにする
			in_model.g_pMaterial[i].Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

			//ファイルの加工
			char buf[256];
			strcpy_s(buf, texturePath);
			strcat_s(buf,pMaterial[i].pTextureFilename);
			in_model.g_pTextureIds[i] = Texture_SetLoadFile(pDevice,buf);
		}
		
	}
	pMaterialBuffer->Release();

}
void UninitModel(Model &in_model)
{
	in_model.g_pMesh->Release();
	delete[] in_model.g_pMaterial;
	for (int i = 0; i < in_model.g_MaterialCount; i++)
	{
		if (in_model.g_pTextureIds[i] < 0) continue;
		Texture_Release(in_model.g_pTextureIds[i], in_model.g_MaterialCount);
	}
	delete[] in_model.g_pTextureIds;

}
void DrawModel(LPDIRECT3DDEVICE9 pDevice,Model &in_model)
{
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE,D3DMCS_MATERIAL);
	for (int i = 0; i < in_model.g_MaterialCount; i++)
	{
		pDevice->SetMaterial(&in_model.g_pMaterial[i]);
		pDevice->SetTexture(0, in_model.g_pTextureIds[i] < 0 ? nullptr : Texture_GetTexture(in_model.g_pTextureIds[i]));
		in_model.g_pMesh->DrawSubset(i);
		pDevice->SetTexture(0, nullptr);
	}	
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);   //make sure the xfile model will not change the light after change the size
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);



}

void UpdateModel(Model& in_model)
{
}

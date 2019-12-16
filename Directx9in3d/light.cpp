#include "light.h"
D3DLIGHT9 light, light2;
//set the direction light
void SetLight(LPDIRECT3DDEVICE9 p_device)
{
	p_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	p_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);


	light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDirLight(-0.0f, -0.6, -1.0f);
	D3DXVec3Normalize(&vecDirLight, &vecDirLight);
	light.Direction = vecDirLight;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;
	p_device->SetLight(0, &light);
	p_device->LightEnable(0, true);
	
	light2.Type = D3DLIGHT_DIRECTIONAL;
	light2.Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
	vecDirLight = D3DXVECTOR3(-0.0f, -1.0f, 0.8f);
	D3DXVec3Normalize(&vecDirLight, &vecDirLight);
	light2.Direction = vecDirLight;
	p_device->SetLight(1, &light2);
	p_device->LightEnable(1, true);
}

#include "light.h"

//set the direction light
void SetLight(LPDIRECT3DDEVICE9 p_device)
{
	D3DLIGHT9 light;
	p_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	p_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);


	light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDirLight(-1.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&vecDirLight, &vecDirLight);
	light.Ambient = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	light.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	light.Direction = vecDirLight;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;
	p_device->LightEnable(0, true);
	p_device->SetLight(0, &light);
	
}

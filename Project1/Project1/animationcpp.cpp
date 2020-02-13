#include  "animation.h"

Scene1 scene1(0.0f,21.0f);
Scene2 scene2(21.4f,40.0f);
//Scene2 scene2(0.0f,100.0f);
LPDIRECT3DDEVICE9 Device;
Star star;
float g_time;


void InitAni()
{
	
	Device = GetD3DDevice();
	scene1.InitScene1(Device);
	scene2.InitScene2(Device);

	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}



void PlayAni(HWND hWnd)
{
	//Device->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	g_time = GetTime();
	if (g_time < 21.0f)
	{
		scene1.GetStarMSG();
		scene1.UpdateScene1(g_time);
		scene1.DrawScene1(Device, hWnd);
	}
	else if (g_time == 21.0f)
	{
		scene1.~Scene1();
	}
    if (g_time > 21.0f && g_time < 100.0f)
	{
		scene2.UpdateScene2(g_time);
		scene2.DrawScene2(Device, hWnd);
	}

}


CenterMSG GetScene1MSG()
{
	return scene1.GetStarMSG();
}
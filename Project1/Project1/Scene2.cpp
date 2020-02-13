#include "Scene2.h"



Scene2::Scene2(float g_startTime, float g_lastTime)
	:startTime(), lastTime()
{
	startTime = g_startTime;
	lastTime = g_lastTime;
}
Scene2::~Scene2()
{
}
void Scene2::InitScene2(LPDIRECT3DDEVICE9 Device)
{
	//the sea
	bk_rect[0].InitRectangleBK({ D3DXVECTOR4(0.0f,400.0f,0.0f,1.0f),D3DCOLOR_RGBA(135,206,250,255) }, 320.0f, 1080.0f);
	bk_rect[1].InitRectangleBK({ D3DXVECTOR4(0.0f,440.0f,0.0f,1.0f),D3DCOLOR_RGBA(123,199,253,255) }, 280.0f, 1080.0f);

	//the hook
	hook_rect[0].InitRectangle({ D3DXVECTOR4(540.0f,-38.0f,0.0f,1.0f),D3DCOLOR_RGBA(0,0,0,255) }, 0.0f, 6.0f);
	hook_rect[1].InitRectangle({ D3DXVECTOR4(534.0f,-38.0f,0.0f,1.0f),D3DCOLOR_RGBA(133, 84 ,0,255) }, 10.0f, 20.0f);
	hook_circle.InitCircle({ D3DXVECTOR4(545.0f,0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255 ,165 ,0,180) }, 30.0f, 40);
	
	
	hook_speed = 16.0f;
	water_force = 30.0f;
	right_force = left_force = 6.0f;

	hook_speedUP = 16.0f;
	star_gravity = 6.0f;
	isShowEffect = false;

	Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surface);
	surface->GetDesc(&surfaceDesc);
	ww2 = new waterWave2(surfaceDesc.Width, surfaceDesc.Height,1088);
	//imageDataDst = new DWORD[(surfaceDesc.Height - 1) * lockedRect.Pitch / 4 + surfaceDesc.Width];
	m_rippling = new Rippling(1088);
}
void Scene2::UpdateScene2(float currentTime)
{
	float lastedTime = currentTime - startTime;
	lastTime = currentTime - startTime;;
	if (lastedTime > 0)
		if (lastedTime < 2.43f)
		{
			if (lastedTime < 1.20f)
			{
				hook_speed *= 0.96f;
				hook_rect[0].ChangeRectangleByLength(hook_speed);
				hook_rect[1].TranslationRectangle(D3DXVECTOR3(0.0f, hook_speed, 0.0f));
				hook_circle.TranslationCircle(D3DXVECTOR4(0.0f, hook_speed, 0.0f, 1.0f));
				//hook_circle[1].TranslationCircle(D3DXVECTOR4(0.0f, hook_speed, 0.0f, 1.0f));
			}
			else if (lastedTime < 1.60f)
			{
				water_force *= 0.7f;
				hook_rect[0].ChangeRectangleByLength(-water_force);
				hook_rect[1].TranslationRectangle(D3DXVECTOR3(0.0f, -water_force, 0.0f));
				hook_circle.TranslationCircle(D3DXVECTOR4(0.0f, -water_force, 0.0f, 1.0f));
			}
			else
			{
				water_force *= 1.2f;
				hook_rect[0].ChangeRectangleByLength(water_force);
				hook_rect[1].TranslationRectangle(D3DXVECTOR3(0.0f, water_force, 0.0f));
				hook_circle.TranslationCircle(D3DXVECTOR4(0.0f, water_force, 0.0f, 1.0f));
			}
		}
		else if (lastedTime < 5.0f)
		{
			if ((hook_circle.GetCenter().y + 15) >= 440.0f && !isShowEffect)
			{
				Position pos;
				pos.x = hook_circle.GetCenter().x;
				pos.y = 550.0f;
				float phase = -D3DX_PI / 2;
				WaterWave ww(pos, 20.0f, phase, 10.0f, 1.0f, false, 1e-12);
				m_rippling->AddWave(ww);
				isShowEffect = true;
				ww2->disturb(pos.x, pos.y,50,100);
			}
		}
	//moveUp
		else if (lastedTime < 6.5f)
		{
			hook_speedUP *= 0.96f;
			hook_rect[0].ChangeRectangleByLength(-hook_speed);
			hook_rect[1].TranslationRectangle(D3DXVECTOR3(0.0f, -hook_speed, 0.0f));
			hook_circle.TranslationCircle(D3DXVECTOR4(0.0f, -hook_speed, 0.0f, 1.0f));
		}
	// move to left
		else if (lastedTime < 8.5f)
		{
			hook_rect[0].TranslationRectangle(D3DXVECTOR3(left_force, 0.0f, 0.0f));
			hook_rect[1].TranslationRectangle(D3DXVECTOR3(left_force, 0.0f, 0.0f));
			hook_circle.TranslationCircle(D3DXVECTOR4(left_force, 0.0f, 0.0f, 1.0f));
			if (lastedTime > 7.6f)
				left_force *= 0.95f;
		}
	// move to right
		else if (lastedTime < 12.5f)
		{
			hook_rect[0].TranslationRectangle(D3DXVECTOR3(-right_force, 0.0f, 0.0f));
			hook_rect[1].TranslationRectangle(D3DXVECTOR3(-right_force, 0.0f, 0.0f));
			hook_circle.TranslationCircle(D3DXVECTOR4(-right_force, 0.0f, 0.0f, 1.0f));
			if (lastedTime > 11.6f)
				right_force *= 0.95f;
			water_force = 10.0f;
		}
		else if (lastedTime < 13.1f)
		{
			hook_rect[0].ChangeRectangleByLength(water_force);
			hook_rect[1].TranslationRectangle(D3DXVECTOR3(0.0f, water_force, 0.0f));
			hook_circle.TranslationCircle(D3DXVECTOR4(0.0f, water_force, 0.0f, 1.0f));
			if (lastedTime > 12.6f)
				water_force *= 0.96f;
		}
		else if (lastedTime < 14.4f)
		{
			hook_speedUP = 16.0f;
		}
		else if (lastedTime < 14.6f)
		{
			star_gravity *= 0.86f;
			hook_rect[0].ChangeRectangleByLength(star_gravity);
			hook_rect[1].TranslationRectangle(D3DXVECTOR3(0.0f, star_gravity, 0.0f));
			hook_circle.TranslationCircle(D3DXVECTOR4(0.0f, star_gravity, 0.0f, 1.0f));

		}
		else if (lastedTime < 14.8f)
		{
			star_gravity = 18.0f;
			star.InitStar({ D3DXVECTOR4(hook_circle.GetCenter().x,hook_circle.GetCenter().y,0.0f,1.0f),D3DCOLOR_RGBA(255,193,37,255) }, 30.0f, 20.0f, 0);
		}
		else if (lastedTime < 17.6f)
		{
			star_gravity *= 0.86f;
			hook_speedUP *= 0.96f;
			hook_rect[0].ChangeRectangleByLength(star_gravity - hook_speedUP);
			hook_rect[1].TranslationRectangle(D3DXVECTOR3(0.0f, star_gravity - hook_speedUP, 0.0f));
			hook_circle.TranslationCircle(D3DXVECTOR4(0.0f, star_gravity - hook_speedUP, 0.0f, 1.0f));
			star.TranslationStar(D3DXVECTOR4(0.0f, star_gravity - hook_speedUP, 0.0f, 1.0f));
		}

	
}
void Scene2::DrawScene2(LPDIRECT3DDEVICE9 Device, HWND hWnd)
{
	//‰æ–Ê‚ÌƒNƒŠƒA
	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);

	//render start
	Device->BeginScene();
	Device->SetFVF(FVF_VERTEX2D);

	bk_rect[0].DrawRectangle(Device);

	hook_rect[0].DrawRectangle(Device);
	hook_rect[1].DrawRectangle(Device);
	
	hook_circle.DrawCircle(Device);
	if (lastTime > 14.6f)
	{
		star.DrawStar(Device);
	}

	
	bk_rect[1].DrawRectangle(Device);

	if (isShowEffect)
	{
		waveEffect2(Device);
		//waveEffect(Device);
	}
	//ww.InitWave(Device);

	Device->EndScene();
	Device->Present(NULL, NULL, NULL, NULL);
}

void Scene2::waveEffect(LPDIRECT3DDEVICE9 g_pdevice)
{
	
	g_pdevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surface);
	surface->GetDesc(&surfaceDesc);
	surface->LockRect(&lockedRect, 0, 0);

	imageData = (DWORD*)lockedRect.pBits;
	imageDataDst = new DWORD[(surfaceDesc.Height - 1) * lockedRect.Pitch / 4 + surfaceDesc.Width];
	for (int i = 0; i < surfaceDesc.Height; i++)
	{
		for (int j = 0; j < surfaceDesc.Width; j++)
		{
			int index = i * lockedRect.Pitch / 4 + j;
			imageDataDst[index] = imageData[index];
		}
	}
	m_rippling->Process(imageData, imageDataDst,  surfaceDesc.Width, surfaceDesc.Height);
	m_rippling->Propagate();
	//for (int i = 0; i < surfaceDesc.Height; i++)
	//{
	//	for (int j = 0; j < surfaceDesc.Width; j++)
	//	{
	//		int index = i * lockedRect.Pitch / 4 + j;
	//		imageData[index] = D3DCOLOR_XRGB(255, 255, 0, 0);
	//		if (i == surfaceDesc.Height - 1 && j == surfaceDesc.Width-1)
	//		{
	//			int s = 0;
	//		}
	//	}
	//}
	surface->UnlockRect();
}

void Scene2::waveEffect2(LPDIRECT3DDEVICE9 g_pdevice)
{
	surface->LockRect(&lockedRect, 0, 0);
	imageDataDst = new DWORD[(surfaceDesc.Height - 1) * lockedRect.Pitch / 4 + surfaceDesc.Width];
	imageData = (DWORD*)lockedRect.pBits;
	for (int i = 0; i < surfaceDesc.Height; i++)
	{
		for (int j = 0; j < surfaceDesc.Width; j++)
		{
			int index = i * lockedRect.Pitch / 4 + j;
			imageDataDst[index] = imageData[index];
		}
	}
	//memcpy(imageDataDst, lockedRect.pBits, sizeof(DWORD));
	ww2->nextFrame();
	ww2->RenderRipple(imageDataDst, imageData);
	surface->UnlockRect();
}
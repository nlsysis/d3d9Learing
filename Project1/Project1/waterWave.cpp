#include "waterWave.h"
#include "D3D9.h"


//DWORD *imageData = (DWORD*)lockedRect.pBits;
WaterWave::WaterWave(Position g_wavePos,float g_maxAmp,float g_InitPhase,float g_waveLen,
				float g_velocity,bool g_isDisappear,float g_curRadius)
	:wavePos(g_wavePos),maxAmp(g_maxAmp),InitPhase(g_InitPhase),waveLen(g_waveLen),
	velocity(g_velocity),isDisappear(g_isDisappear),curRadius(g_curRadius)
{
	wavePos = g_wavePos;
	maxAmp = g_maxAmp;
	InitPhase = g_InitPhase;
	waveLen = g_waveLen;
	velocity = g_velocity;
	isDisappear = g_isDisappear;
	curRadius = g_curRadius;
	time = 0.0f;
}

//WaterWave::WaterWave()
//{}
WaterWave::~WaterWave()
{}
//void WaterWave::InitWave()
//{
//	wavePos = g_pos;
//	maxAmp = g_maxAmp;
//	InitPhase = g_InitPhase;
//	waveLen = g_waveLen;
//	velocity = g_velocity;
//	isDisappear = g_isDisappear;
//	curRadius = g_curRadius;
//	time = 0.0f;
//	
//}
void WaterWave::DrawWave()
{
	
}
bool WaterWave::Propagete()
{
	time++;
	curRadius += velocity;
	//to low the wave
	maxAmp /= 1.01f;

	if (maxAmp < 1e-3)   //1e-3 = 0.001
	{
		isDisappear = true;
	}
	return isDisappear;
}
void WaterWave::GetAmplitude(int x, int y, float& ax, float &ay)
{
	
	ax = ay = 0.0f;
	//if the wave is disappear don't calculate
	if (isDisappear) return;

	float dx = wavePos.x - x;
	float dy = wavePos.y - y;

	float dist = dx * dx + dy * dy;
	// the distance is far than the radius
	if (dist > curRadius * curRadius || dist == 0) return;
	if (x >= 545 && y >= 440)
	{
		int xs = x;

	}
	dist = sqrt(dist);
	float r = 1 - dist / 1000.0f;
	float g_MaxAmp = maxAmp * r;

	float temp = 2 * D3DX_PI *(velocity * time - dist) / waveLen + InitPhase;
	float curAmp = maxAmp * sin(temp);

	ax = curAmp * abs((int)(dx))/ dist;
	ay = curAmp * abs((int)(dy)) / dist;
}


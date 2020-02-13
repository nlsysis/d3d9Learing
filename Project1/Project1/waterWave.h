#pragma once
#include "polygon.h"


class WaterWave
{
public:
	WaterWave(Position g_wavePos, float g_maxAmp, float g_InitPhase, float g_waveLen,
		float g_velocity, bool g_isDisappear, float g_curRadius);
	WaterWave();
	~WaterWave();
	/*void InitWave(Position g_pos, float g_maxAmp, float g_InitPhase, float g_waveLen,
		float g_velocity, bool g_isDisappear, float g_curRadius);*/
	void DrawWave();
	bool Propagete();
	void GetAmplitude(int x,int y,float& ax,float &ay);
private:
	Position wavePos;
	float maxAmp;
	float InitPhase;
	float waveLen;
	float velocity;
	bool isDisappear;
	float curRadius;
	int time;
};
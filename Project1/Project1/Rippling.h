#pragma once
#include "polygon.h"
#include "waterWave.h"
#include <list>
using namespace std;
typedef unsigned char u8;


class Rippling
{
public:
	Rippling(int g_pitch);
	~Rippling();
	void AddWave(WaterWave &wave);
	void Process(DWORD *puDst, DWORD *puSrc, int nWidth, int nHeight);
	void Propagate();
	void DrawRippling(LPDIRECT3DDEVICE9 g_pdevice);
private:
	void GetPos(float &x, float &y);
	void GetSubPixel(DWORD *puDst, DWORD *puSrc, int nWidth, int nHeight, float x, float y);
	list<WaterWave> m_WaveList;
	int pitch;
};
#pragma once
#include "polygon.h"
class waterWave2
{
public:
	waterWave2(int waterWidth, int waterHeight, int g_pitch);
	~waterWave2();
	void disturb(int x, int y, int stonesize, int stoneweight);
	void RenderRipple(DWORD *Texture, DWORD *Target);
	void nextFrame();
private:
	short *buf;
	short *buf2;
	int waterWidth;
	int waterHeight;
	int pitch;
};
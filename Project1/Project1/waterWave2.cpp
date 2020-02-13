#include "waterWave2.h"

waterWave2::waterWave2(int g_waterWidth, int g_waterHeight,int g_pitch)
{
	waterWidth = g_waterWidth;
	waterHeight = g_waterHeight;
	pitch = g_pitch;
	buf = new short[waterWidth * waterHeight]();
	buf2 = new short[waterWidth * waterHeight]();

}

waterWave2::~waterWave2()
{
}

void waterWave2::disturb(int x, int y, int stonesize, int stoneweight)
{
	if ((x >= waterWidth - stonesize) ||
		(x < stonesize) ||
		(y >= waterHeight - stonesize) ||
		(y < stonesize))
		return;

	for (int posx = x - stonesize; posx < x + stonesize; posx++)
	{
		for (int posy = y - stonesize; posy < y + stonesize; posy++)
		{
			if ((posx - x)*(posx - x) + (posy - y)*(posy - y) < stonesize * stonesize)
			{
				buf[waterWidth * posy + posx] += stoneweight;
			}
		}
	}
}

void waterWave2::RenderRipple(DWORD* Texture, DWORD* Target)
{
	int i = 0;
	for (int y = 0; y < waterHeight; y++)
	{
		for (int x = 0; x < waterWidth; x++)
		{
			short data = 1024 - buf[i];

			// 偏移
			int teX = ((x - waterWidth / 2) * data >> 10) + waterWidth / 2;
			int teY = ((y - waterHeight / 2) * data >> 10) + waterHeight / 2;

			// 边界处理
			if (teX >= waterWidth)	teX = waterWidth - 1;
			if (teX < 0)				teX = 0;
			if (teY >= waterHeight)	teY = waterHeight - 1;
			if (teY < 0)				teY = 0;
			if (buf[i] != 0)
			{
				int ss = 0;
			}
			// 处理偏移 
			Target[x + y * pitch] = Texture[teX + (teY * pitch)];
			i++;
		}
	}
}

// 计算出下一个时刻所有点的波幅
void waterWave2::nextFrame()
{
	for (int i = waterWidth; i < waterHeight*(waterWidth - 1); i++)
	{
		// 公式：X0'= (X1+X2+X3+X4) / 2 - X0
		buf2[i] = ((buf[i - waterWidth] + buf[i + waterWidth] + buf[i - 1] + buf[i + 1]) >> 1) - buf2[i];

		// 波能衰减
		buf2[i] -= buf2[i] >> 5;
	}

	short *ptmp = buf;
	buf = buf2;
	buf2 = ptmp;
}

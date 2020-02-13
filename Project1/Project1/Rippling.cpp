#include "Rippling.h"
#include "D3D9.h"


//DWORD *imageData = (DWORD*)lockedRect.pBits;
Rippling::Rippling(int g_pitch)
{
	pitch = g_pitch;
}
Rippling::~Rippling()
{}
void Rippling::DrawRippling(LPDIRECT3DDEVICE9 g_pdevice)
{
	
}

void Rippling::AddWave(WaterWave &wave)
{
	m_WaveList.push_back(wave);
}
void Rippling::Process(DWORD *puDst, DWORD *puSrc, int nWidth, int nHeight)
{
	int nRow, nCol;
	float x, y;
	for (nRow = 0; nRow < nHeight; nRow++)
	{
		for (nCol = 0; nCol < nWidth; nCol++)
		{
			x = nCol;
			y = nRow;
			GetPos(x, y);   //坐标偏移
			//GetSubPixel(puDst, puSrc, nWidth, nHeight, x, y);
			if (x != nCol && y != nRow)
			{
				int ss = 0;
			}
			puDst[nCol + nRow * pitch] = puSrc[(int)x+(int)y* pitch];
			//puDst += nChannels;
		}
	}
}
//每个波源都需要传播
void Rippling::Propagate()
{
	list<WaterWave>::iterator it = m_WaveList.begin();
	while (it != m_WaveList.end())
	{
		bool bDisappear = it->Propagete();
		if (bDisappear)
			it = m_WaveList.erase(it);
		else it++;
	}
}
void Rippling::GetPos(float &x, float &y)
{
	float fAmpx = 0;
	float fAmpy = 0;
	list<WaterWave>::iterator it = m_WaveList.begin();
	while (it != m_WaveList.end())
	{
		it->GetAmplitude(x, y, fAmpx, fAmpy);
		/*if (fAmpx != 0 || fAmpy != 0)
		{
			x += fAmpx;
		}*/
		x += fAmpx;
		y += fAmpy;
		it++;
		if (fAmpx != 0)
		{
			int test = y;
		}
	}
}
void Rippling::GetSubPixel(DWORD *puDst, DWORD *puSrc,
	int nWidth, int nHeight, float x, float y)
{
	int x0 = x;
	int y0 = y;
	int x1 = x0 + 1;
	int y1 = y0 + 1;

	float wx1 = x - x0;
	float wy1 = y - y0;
	float wx0 = 1.0f - wx1;
	float wy0 = 1.0f - wy1;

	x0 = max(x0, 0);
	x1 = max(x1, 0);
	y0 = max(y0, 0);
	y1 = max(y1, 0);

	x0 = min(x0, nWidth - 1);
	x1 = min(x1, nWidth - 1);
	y0 = min(y0, nHeight - 1);
	y1 = min(y1, nHeight - 1);
	
	DWORD Y0 = puSrc[y0 * pitch + x0];
	DWORD Y1 = puSrc[y1 * pitch + x1];
	float sum_y0 = Y0 * wx0 + Y0 * wx1;
	float sum_y1 = Y1 * wx0 + Y1 * wx1;
	//float sum_y = sum_y0 * wy0 + sum_y1 * wy1;
	puDst[x0 + y0 * pitch] = (DWORD)(Y0 + Y1);

	/*for (int i = 0; i < nChannels; i++)
	{
		DWORD* Y0 = puSrc + y0 * nWidth * nChannels;
		DWORD* Y1 = puSrc + y1 * nWidth * nChannels;
		float sum_y0 = (Y0[x0 * nChannels + i] * wx0 + Y0[x1 * nChannels + i] * wx1);
		float sum_y1 = (Y1[x0 * nChannels + i] * wx0 + Y1[x1 * nChannels + i] * wx1);
		puDst[i] = (DWORD)(sum_y0 * wy0 + sum_y1 * wy1);
	}*/

}


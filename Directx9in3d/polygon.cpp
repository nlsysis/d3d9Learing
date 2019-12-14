#include "polygon.h"


void InitPolygon()
{
	

}
void UninitPolygon() 
{

}
void UpdatePolygon() 
{

}

void DrawPolygon(LPDIRECT3DDEVICE9 p_device)
{
	p_device->SetFVF(FVF_VERTEX2D);
	p_device->DrawPrimitiveUP(D3DPT_LINELIST, 3, v, sizeof(Vertex2d));
}
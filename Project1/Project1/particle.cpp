#include "particle.h"
#include "main.h"
#include "Circle.h"
#include <time.h>
#include "animation.h"

MoveParticle g_particle[NUM_MAX];
Position g_preMousePos;
float mouseVX, mouseVY;
CenterMSG m_mouse;
Circle g_ball[NUM_MAX];

float toDist, blowDist, striDist;
void InitParticle()
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < NUM_MAX; i++)
	{
		g_particle[i].color = D3DCOLOR_RGBA(238, 201, 0, rand() % 256);
		g_particle[i].radius = (rand() % 34);
		g_particle[i].x = rand() % SCREEN_WIDTH;
		g_particle[i].y = rand() % SCREEN_HEIGHT;
		g_particle[i].vx = cos(i) * (rand() % 34);
		g_particle[i].vy = sin(i) * (rand() % 34);
	}

	m_mouse.position.x = g_preMousePos.x = SCREEN_WIDTH / 2;
	m_mouse.position.y = g_preMousePos.y = SCREEN_HEIGHT / 2;
	m_mouse.isLeftDown = false;

	toDist = 0.5 * SCREEN_WIDTH;   // in this area the ball will be attracted
	blowDist = 0.25 * SCREEN_WIDTH;  //in this area the ball will be excluded
	striDist = 0.08 * SCREEN_WIDTH; //in this area the ball will be influedced by mouse
}
void UninitParticle()
{

}

void UpdateParticle()
{
	m_mouse = GetScene1MSG();

	//the speed of moving mouse
	mouseVX = m_mouse.position.x - g_preMousePos.x;
	mouseVY = m_mouse.position.y - g_preMousePos.y;

	g_preMousePos.x = m_mouse.position.x;
	g_preMousePos.y = m_mouse.position.y;

	for (int i = 0; i < NUM_MAX; i++)
	{
		float x = g_particle[i].x;
		float y = g_particle[i].y;
		float vx = g_particle[i].vx;
		float vy = g_particle[i].vy;

		float dx = x - m_mouse.position.x;
		float dy = y - m_mouse.position.y;

		float distance = sqrt(dx * dx + dy * dy);

		if (distance != 0)
		{
			dx = dx / distance;
			dy = dy / distance;
		}
		else
		{
			dx = 0;
			dy = 0;
		}

		if (distance < toDist)
		{
			float toAcc = (1 - (distance / toDist)) * SCREEN_WIDTH * 0.0014f;

			//make the ball move to the mouse
			vx -= dx * toAcc;
			vy -= dy * toAcc;
		}
		if (m_mouse.isLeftDown && distance < blowDist)
		{
			float blowAcc = (1 - (distance / blowDist)) * 10;
			
			//make the ball leave the mouse
			vx += dx * blowAcc + 0.5f - rand() / RAND_MAX;
			vy += dy * blowAcc + 0.5f - rand() / RAND_MAX;
		}
		if (distance < striDist)
		{
			float mAcc = (1 - (distance / toDist)) * SCREEN_WIDTH * 0.00026f;
			
			//make the ball leave the mouse
			vx += mouseVX * mAcc;
			vy += mouseVY * mAcc;
		}

		vx *= FRICTION;
		vy *= FRICTION;

		float avgVX = fabs(vx);
		float avgVY = fabs(vy);
		float avgV = (avgVX + avgVY) * 0.5f;
		 
		if (avgVX < 0.1)
			vx *= float(rand()) / RAND_MAX * 3;
		if (avgVY < 0.1)
			vy *= float(rand()) / RAND_MAX * 3;

		//if the radius in [0.4,3.5] the radius will bigger with speed
		float sc = avgV * 0.45f;
		sc = max(min(sc, 3.5f), 0.4f);
		
		x += vx;
		y += vy;

		if (x >= SCREEN_WIDTH)
		{
			x = SCREEN_WIDTH;
			vx *= -1.0f;
		}
		if (x <= 0)
		{
			x = 0;
			vx *= -1.0f;
		}
		if (y >= SCREEN_HEIGHT)
		{
			y = SCREEN_HEIGHT;
			vy *= -1.0f;
		}
		if (y <= 0)
		{
			y = 0;
			vy *= -1.0f;
		}
		g_particle[i].radius = sc;
		g_particle[i].x = x;
		g_particle[i].y = y;
		g_particle[i].vx = vx;
		g_particle[i].vy = vy;
	}
}
void DrawParticle(LPDIRECT3DDEVICE9 device)
{
	for (int i = 0; i < NUM_MAX; i++)
	{
		g_ball->InitCircle({ D3DXVECTOR4(g_particle[i].x,g_particle[i].y,0.0f,1.0f),
			g_particle[i].color }, g_particle[i].radius, 40);
		g_ball->DrawCircle(device);
	}
}


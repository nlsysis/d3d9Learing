#pragma once
#include "main.h"

struct Sphere
{
	D3DXVECTOR3 center;
	float radius;
};

bool IsHitSphereCollision(const Sphere &A,const Sphere&B)
{
	float length = D3DXVec3LengthSq(&(A.center - B.center));
	return (A.radius + B.radius)* (A.radius + B.radius) > length;
}
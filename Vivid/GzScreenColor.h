#pragma once
#include "GzColor.h"
class GzScreenColor :
	public GzColor
{
public:
	GzScreenColor(float r, float g, float b, float a = 1.0, float z = -INT_MAX);
	float Zbuffer;
};


#pragma once
#include "GzPoint.h"
class GzRectangle
{
public:
	GzRectangle();
	GzRectangle(GzPoint& topleft, GzPoint& bottomright);
	GzRectangle(float l, float t, float r, float b);
	float Left;
	float Top;
	float Right;
	float Bottom;
};


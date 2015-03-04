#include "stdafx.h"
#include "GzPoint.h"

GzPoint::GzPoint()
	: x(0.0), y(0.0), z(0.0)
{
}

GzPoint::GzPoint(float coords[])
{
	x = coords[0];
	y = coords[1];
	z = coords[2];
}

GzPoint::GzPoint(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{
}

GzPoint::~GzPoint()
{
}

GzPoint GzPoint::operator = (const GzPoint& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

GzPoint GzPoint::operator-(const GzPoint& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}
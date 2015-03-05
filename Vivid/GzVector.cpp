/*
	File name:		GzVector.cpp
	Description:	Implementation of the GzVector class.
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-02
*/

#include "stdafx.h"
#include "GzVector.h"


GzVector::GzVector()
	: GzPoint()
{
}

GzVector::GzVector(float _x, float _y, float _z)
	: GzPoint(_x, _y, _z)
{
}

GzVector::GzVector(float coords[3])
	: GzPoint(coords)
{
}

GzVector::GzVector(const GzPoint& begin, const GzPoint& end)
{
	x = end.x - begin.x;
	y = end.y - begin.y;
	z = end.z - begin.z;
}

GzVector::~GzVector()
{
}

GzVector GzVector::Normalize()
{
	float mag = sqrt(x*x + y*y + z*z);
	x /= mag;
	y /= mag;
	z /= mag;
	return *this;
}

float GzVector::GetMagnitude()
{
	return sqrt(x*x + y*y + z*z);
}
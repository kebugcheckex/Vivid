/*
	File name:		GzPoint.h
	Description:	Implementation of the GzPoint class.
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-02
	Contributor:	Xinyu Chen
*/

#include "stdafx.h"
#include "GzPoint.h"

GzPoint::GzPoint()
{
}

GzPoint::GzPoint(float *coords, int dim)
{
	X = coords[0];
	Y = coords[1];
	if (dim > 2) Z = coords[2];
	else Z = 0.0;
	if (dim > 3) W = coords[3];
	else W = 0.0;
}

GzPoint::GzPoint(float x, float y, float z, float w)
	: X(x), Y(y), Z(z), W(w)
{
}

GzPoint GzPoint::operator = (const GzPoint& rhs)
{
	X = rhs.X;
	Y = rhs.Y;
	Z = rhs.Z;
	W = rhs.W;
}

GzPoint GzPoint::operator-(const GzPoint& rhs)
{
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;
	W -= rhs.W;
	return *this;
}

float GzPoint::Distance(const GzPoint& pa, const GzPoint& pb)
{
	return sqrt((pa.X - pb.X) * (pa.X - pb.X) +
		(pa.Y - pb.Y) * (pa.Y - pb.Y) +
		(pa.Z - pb.Z) * (pa.Z - pb.Z));
}
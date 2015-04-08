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
{	// Default constructor
}

GzVector::GzVector(float x, float y, float z, float w)
	: GzPoint(x, y, z, w)
{	// Initialize with x, y, z values
}

GzVector::GzVector(float *coords, int dim)
	: GzPoint(coords, dim)
{	// Initialize with an array of float numbers
}

GzVector::GzVector(const GzPoint& begin, const GzPoint& end)
{	// Initialize with two coordinates
	X = end.X - begin.X;
	Y = end.Y - begin.Y;
	Z = end.Z - begin.Z;
	W = end.W - begin.W;
}

GzVector GzVector::Normalize()
{
	float mag = GetMagnitude();
	X /= mag;
	Y /= mag;
	Z /= mag;
	return *this;	// This function both modifies the "this" class and return itself
}

float GzVector::GetMagnitude()
{
	return sqrt(X*X + Y*Y + Z*Z);
}

float& GzVector::operator [] (const int index)
{
	switch (index)
	{
	case 0:
		return X;
		break;
	case 1:
		return Y;
		break;
	case 2:
		return Z;
		break;
	case 3:
		return W;
		break;
	default:
		// TODO - Throw some exception, but I have not implemented exception class yet.
		break;
	}
}

void GzVector::operator - ()
{
	X = -X;
	Y = -Y;
	Z = -Z;
	W = -W;
}

GzVector& GzVector::operator = (const GzVector& rhs)
{
	X = rhs.X;
	Y = rhs.Y;
	Z = rhs.Z;
	W = rhs.W;
	return *this;
}

inline GzVector& GzVector::operator += (const GzVector& rhs)
{
	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;
	W += rhs.W;
	return *this;
}

GzVector operator + (const GzVector& lhs, const GzVector& rhs)
{
	GzVector ret{ lhs };
	return ret += rhs;
}

GzVector& GzVector::operator -= (const GzVector& rhs)
{
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;
	W -= rhs.W;
	return *this;
}

GzVector operator - (const GzVector& lhs, const GzVector& rhs)
{
	GzVector ret{ lhs };
	return ret -= rhs;
}

GzVector& GzVector::operator *= (const float& rhs)
{
	X *= rhs;
	Y *= rhs;
	Z *= rhs;
	W *= rhs;
	return *this;
}

GzVector operator * (const GzVector& lhs, const float& rhs)
{
	GzVector ret{ lhs };
	return ret *= rhs;
}

GzVector operator * (const float& lhs, const GzVector& rhs)
{
	GzVector ret{ rhs };
	return ret *= lhs;
}

float operator * (const GzVector& lhs, const GzVector& rhs)
{
	float ret = lhs.X * rhs.X
		+ lhs.Y * rhs.Y
		+ lhs.Z * rhs.Z
		+ lhs.W * rhs.W;
	return ret;
}

GzVector operator ^ (const GzVector& lhs, const GzVector& rhs)
{	// For cross-product, we only do three dimensional, ignoring w value
	float x = lhs.Y*rhs.Z - lhs.Z*rhs.Y;
	float y = lhs.Z*rhs.X - lhs.X*rhs.Z;
	float z = lhs.X*rhs.Y - lhs.Y*rhs.X;
	GzVector ret{ x, y, z };
	return ret;
}
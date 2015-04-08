/*
	File name:		GzPoint.h
	Description:	Definition of the GzPoint class. This class implements a
					point in three dimensional space, with one extra dimension,
					along with its operations
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-02
	Contributor:	Xinyu Chen
*/

#pragma once
class GzPoint
{
public:
	// Constructors
	GzPoint();
	GzPoint(float *coords, int dim);
	/* Initialize with two or three coordinates */
	GzPoint(float x, float y, float z = 0, float w = 0);
public:
	float X;
	float Y;
	float Z;
	float W;
	// Operators
	GzPoint operator = (const GzPoint& rhs);
	GzPoint operator - (const GzPoint& rhs);
	// Tool functions are defined as static members
	static float Distance(const GzPoint& pa, const GzPoint& pb);
};


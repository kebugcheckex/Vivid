/*
	File name:		GzLine.h
	Description:	Definition of the GzLine class. This class implements a
					line equation in two dimensional space
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-12

	Contributors:	Xinyu Chen
*/

#pragma once
#include "GzVector.h"
class GzLine
{
public:
	GzLine();
	/* Construct a line with two points */
	GzLine(const GzPoint& pa, const GzPoint& pb);
	/* Construct a line with a vector and a point */
	GzLine(const GzVector& v, const GzPoint& p);
	~GzLine();
public:
	/* Check whether a point is on this line */
	bool IsOnTheLine(const GzPoint& p);
	/* Check which size a point is to the line */
	int WhichSide(const GzPoint& p);
private:
	float A, B, C; // Line equation coefficients
};

/*
	TODO -
	This class can be abstracted into a virtual class.
	And derives two subclasses for 2D and 3D space.
*/

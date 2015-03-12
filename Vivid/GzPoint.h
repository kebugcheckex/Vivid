/*
	File name:		GzPoint.h
	Description:	Definition of the GzPoint class. This class implements a
					point in three dimensional space, along with its operations
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-02
*/

#pragma once
class GzPoint
{
public:
	// Constructors
	GzPoint();
	GzPoint(float coords[]);
	GzPoint(float _x, float _y, float _z);
	// Destrutor
	~GzPoint();
public:
	// Public member variables
	float x;
	float y;
	float z;
	// Operators
	GzPoint operator = (const GzPoint& rhs);
	GzPoint operator - (const GzPoint& rhs);
};


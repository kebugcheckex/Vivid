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


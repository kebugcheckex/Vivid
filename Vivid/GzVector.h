#pragma once
#include "GzPoint.h"
class GzVector :
	public GzPoint
{
public:
	// Constructors
	GzVector();
	/* Initialize with x, y, z values. */
	GzVector(float _x, float _y, float _z);
	/* Initialize with two coordinates. */
	GzVector(const GzPoint& begin, const GzPoint& end);
	// Destructor
	~GzVector();
public:
	// Operators
	GzVector operator - ();	// Unary minus
	GzVector operator + (const GzVector& rhs);	// Vector addition
	GzVector operator - (const GzVector& rhs);	// Vector subtraction
	GzVector operator * (const float& rhs);		// Scalar product (scalar on the right)
	friend GzVector operator * (const float& lhs, const GzVector& rhs);	// Scalar product (scalar on the left)
	friend float operator * (const GzVector& lhs, const GzVector& rhs);	// Dot product
	friend GzVector operator ^ (const GzVector& lhs, const GzVector& rhs);	// Cross product
	//GzVector operator / (const float& rhs);
	/*
		In order to prevent confusion, I decide not to define a division operation
		Instead, division can be carried out by using 1 to divide the scalar
	*/

	/* Normalize the vector, return itself. */
	GzVector Normalize();
};


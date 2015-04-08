/*
	File name:		GzVector.h
	Description:	Definition of the GzVector class. This class implements the three dimensional
					vector data structure along with its operations, such as dot product and
					cross product.
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-02
*/

#pragma once
#include "GzPoint.h"
class GzVector :
	public GzPoint
{
public:
	// Default constructor
	GzVector();

	// Initialize with x, y, z values
	GzVector(float x, float y, float z = 0, float w = 0);

	// Initialize with an array of float numbers
	GzVector(float *coords, int dim);

	// Initialize with two coordinates
	GzVector(const GzPoint& begin, const GzPoint& end);

	// Subscript operator, supports both read and write
	float& operator [] (const int index);

	// Unary minus
	void operator - ();

	// Value copy
	GzVector& operator = (const GzVector& rhs);

	// Add to itself
	GzVector& operator += (const GzVector& rhs);

	// Vector addition
	friend GzVector operator + (const GzVector& lhs, const GzVector& rhs);
	
	// Subtract from itself
	GzVector& operator -= (const GzVector& rhs);

	// Vector subtraction
	friend GzVector operator - (const GzVector& lhs, const GzVector& rhs);
	
	// Scalar product to itself (scalar on the right)
	GzVector& operator *= (const float& rhs);

	// Scalar product (scalar on the right)
	friend GzVector operator * (const GzVector& lhs, const float& rhs);
	
	// Scalar product (scalar on the left)
	friend GzVector operator * (const float& lhs, const GzVector& rhs);

	// Dot product
	friend float operator * (const GzVector& lhs, const GzVector& rhs);

	// Cross product
	friend GzVector operator ^ (const GzVector& lhs, const GzVector& rhs);

	//GzVector operator ^= (const GzVector& rhs);
	/*
		Cross-product is not commutative. Therefore it is not a good idea to implement
		a ^= operator.
	*/

	//GzVector operator / (const float& rhs);
	/*
		In order to prevent confusion, I decide not to define a division operation
		Instead, division can be carried out by using 1 to divide the scalar
	*/

	/* Normalize the vector, return itself. */
	GzVector Normalize();

	/* Get the magnitude of the vector. */
	float GetMagnitude();
};


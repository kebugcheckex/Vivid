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
	// Constructors
	GzVector();
	/* Initialize with x, y, z values. */
	GzVector(float _x, float _y, float _z);
	/* Initialize with an array of float numbers. */
	GzVector(float *coords, int dim);
	/* Initialize with two coordinates. */
	GzVector(const GzPoint& begin, const GzPoint& end);
	// Destructor
	~GzVector();
public:
	// Operators
	float& operator [] (int index);
	GzVector operator - ();	// Unary minus
	GzVector operator = (const GzVector& rhs);	// Value copy
	friend GzVector operator + (const GzVector& lhs, const GzVector& rhs);	// Vector addition
	GzVector operator += (const GzVector& rhs);		// Add to itself
	friend GzVector operator - (const GzVector& lhs, const GzVector& rhs);	// Vector subtraction
	GzVector operator -= (const GzVector& rhs);		// Subtract from itself
	friend GzVector operator * (const GzVector& lhs, const float& rhs);		// Scalar product (scalar on the right)
	GzVector operator *= (const float& rhs);		// Scalar product to itself (scalar on the right)
	friend GzVector operator * (const float& lhs, const GzVector& rhs);		// Scalar product (scalar on the left)
	friend float operator * (const GzVector& lhs, const GzVector& rhs);		// Dot product
	friend GzVector operator ^ (const GzVector& lhs, const GzVector& rhs);	// Cross product
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


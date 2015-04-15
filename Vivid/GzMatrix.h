/*
	File name:		GzMatrix.h
	Description:	Definition of a 4x4 matrix. This class implements a 4x4 matrix data structure
					and its operations with vectors and other matrices.
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-05
*/
#pragma once
#include "GzVector.h"

typedef enum tagMatrixType
{
	MATRIX_ZEROS,
	MATRIX_EYE,
	MATRIX_ONES
} MatrixType;

typedef enum tagRotateAxis
{
	ROTATE_X,
	ROTATE_Y,
	ROTATE_Z
} RotateAxis;

class GzMatrix
{
public:
	/* Default constructor */
	GzMatrix();
	
	/* Initialize the matrix with a specific type */
	GzMatrix(MatrixType type);

	/* Initialize a rotation matrix */
	GzMatrix(RotateAxis, float degree);

	/* Initialize with four column vectors */
	GzMatrix(GzVector *vectors);

	/* Get a value in the matrix */
	float Get(int x, int y) const;

	/* Get a column in the matrix */
	GzVector GetColumn(int col) const;

	/* Get a row in the matrix */
	GzVector GetRow(int row) const;

	/* Set a value in the matrix */
	void Set(int x, int y, float val);

	/* Set a column in the matrix */
	void SetColumn(int col, GzVector& vec);

	/* Set a row in the matrix */
	void SetRow(int row, GzVector& vec);

	/* Matrix multiplies a vector */
	friend GzVector operator * (const GzMatrix& lhs, const GzVector& rhs);

	/* Matrix multiplication */
	friend GzMatrix operator * (const GzMatrix& lhs, const GzMatrix& rhs);

	/* Matrix multiplies a scalar on the right */
	friend GzMatrix operator * (const GzMatrix& lhs, const float rhs);
	GzMatrix operator *= (const float rhs);

	/* Matrix multiplies a scalar on the left */
	friend GzMatrix operator * (const float lhs, const GzMatrix& rhs);
private:
	float elements_[4][4];
};


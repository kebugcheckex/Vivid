#pragma once
#include "GzVector.h"

typedef enum tagMatrixType
{
	MATRIX_ZEROS,
	MATRIX_EYE,
	MATRIX_ONES
} MatrixType;
class GzMatrix
{
public:
	/* Default constructor */
	GzMatrix();
	
	// Initialize the matrix with a specific type
	GzMatrix(MatrixType type);
	/* Initialize with four column vectors */
	GzMatrix(GzVector *vectors);
	float Get(int x, int y);
	void Set(int x, int y, float val);
	void SetColumn(int col, const GzVector& vec);
	void SetRow(int row, const GzVector& vec);
	friend GzVector operator * (const GzMatrix& lhs, const GzVector& rhs);
	friend GzMatrix operator * (const GzMatrix& lhs, const GzMatrix& rhs);
private:
	float elements_[4][4];
};


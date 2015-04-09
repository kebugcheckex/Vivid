#include "stdafx.h"
#include "GzMatrix.h"


GzMatrix::GzMatrix()
{
	memset(elements_, 0, sizeof(float) * 16);
}

GzMatrix::GzMatrix(MatrixType type)
{
	switch (type)
	{
	case MATRIX_ZEROS:
		memset(elements_, 0, sizeof(float) * 16);
		break;
	case MATRIX_ONES:
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				elements_[i][j] = 1;
			}
		}
		break;
	case MATRIX_EYE:
		memset(elements_, 0, sizeof(float) * 16);
		for (int i = 0; i < 4; i++)
		{
			elements_[i][i] = 1;
		}
		break;
	default:
		break;
	}
}

GzVector operator * (GzMatrix& lhs, GzVector& rhs)
{
	
}
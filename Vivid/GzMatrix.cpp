#include "stdafx.h"
#include "GzMatrix.h"


GzMatrix::GzMatrix()
{
	memset(elements_, 0, sizeof(float) * 16);
}

GzVector operator * (GzMatrix& lhs, GzVector& rhs)
{
	float result[4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i] += lhs[i][j] * rhs[j];
		}
	}
}
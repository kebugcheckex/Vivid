/*
	File name:		GzMatrix.cpp
	Description:	Implementation of the GzMatrix class
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-05
*/

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

float GzMatrix::Get(int x, int y) const
{
	return elements_[x][y];
}


GzVector GzMatrix::GetColumn(int col) const
{
	GzVector ret;
	for (int i = 0; i < 4; i++)
	{
		ret[i] = elements_[i][col];
	}
	return ret;
}

GzVector GzMatrix::GetRow(int row) const
{
	GzVector ret;
	for (int i = 0; i < 4; i++)
	{
		ret[i] = elements_[row][i];
	}
	return ret;
}

void GzMatrix::Set(int x, int y, float val)
{
	elements_[x][y] = val;
}

void GzMatrix::SetColumn(int col, GzVector& vec)
{
	for (int i = 0; i < 4; i++)
	{
		elements_[i][col] = vec[i];
	}
}

void GzMatrix::SetRow(int row, GzVector& vec)
{
	for (int i = 0; i < 4; i++)
	{
		elements_[row][i] = vec[i];
	}
}
GzVector operator * (GzMatrix& lhs, GzVector& rhs)
{
	GzVector res;
	for (int j = 0; j < 4; j++) {
		res[j] = lhs.GetRow(j) * rhs;
	}
	return res;
}

GzMatrix operator * (const GzMatrix& lhs, const GzMatrix& rhs)
{
	GzMatrix res;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			float sum = 0;
			for (int k = 0; k < 3; k++)
			{
				sum += lhs.elements_[i][k] * rhs.elements_[k][i];
			}
			res.elements_[i][j] = sum;
		}
	}
	return res;
}